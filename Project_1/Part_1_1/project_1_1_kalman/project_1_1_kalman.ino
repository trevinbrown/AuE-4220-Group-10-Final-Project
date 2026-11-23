// AuE 4220 — Project 1.1: one HC-SR04 with a 1D Kalman filter
// HC-SR04: TRIG D13, ECHO D12, 5V, GND. External LED: D6 -> resistor -> LED -> GND.
// Serial output: START, followed by "distance_mm, time_variance_us2", then elapsed_ms.

#include <math.h>

const byte TRIG_PIN = 13;
const byte ECHO_PIN = 12;
const byte LED_PIN  = 6;

const unsigned long PING_INTERVAL_MS = 60;     // HC-SR04: avoid echoes from prior pulses
const unsigned long ECHO_TIMEOUT_US = 12000;  // Covers the 1.5 m test range
const unsigned long MIN_ECHO_US = 850;        // Outside the expected 0.2-1.5 m range
const unsigned long MAX_ECHO_US = 9800;

// Linear regression from the team's six calibration measurements (2026-11-23).
const float MM_PER_US = 0.17287267f;
const float OFFSET_MM = 8.40706f;

// Observed sample variances (microseconds squared) from calibration.
// Interpolate R by echo time instead of assuming constant noise at every distance.
const byte N_CAL = 6;
const float CAL_TIME_US[N_CAL] = {
  1095.03f, 1717.03f, 2844.47f, 4252.21f, 5753.57f, 8630.47f
};
const float CAL_R_US2[N_CAL] = {
  32.37f, 22.29f, 75.48f, 82.92f, 292.29f, 170.80f
};

// State x = filtered echo time [us]; P = uncertainty in x [us^2].
// Stationary-target model: x(k) = x(k-1) + process noise.
const float Q_US2 = 0.50f;        // Model/process-noise variance per update
const float CONVERGED_P_US2 = 25.0f;
const float MAX_CHANGE_MM = 1.0f;
const byte STABLE_UPDATES_REQUIRED = 4;

unsigned long startMillis;
unsigned long lastPingMillis = 0;
bool firstPing = true;
bool finished = false;

unsigned long startupEchoes[3];
byte startupCount = 0;
bool kalmanReady = false;

float xUs = 0.0f;
float PUs2 = 0.0f;
float previousDistanceMm = 0.0f;
byte stableUpdates = 0;

float measurementVariance(float tUs) {
  if (tUs <= CAL_TIME_US[0]) return CAL_R_US2[0];
  if (tUs >= CAL_TIME_US[N_CAL - 1]) return CAL_R_US2[N_CAL - 1];

  for (byte i = 0; i < N_CAL - 1; i++) {
    if (tUs <= CAL_TIME_US[i + 1]) {
      float fraction = (tUs - CAL_TIME_US[i]) /
                       (CAL_TIME_US[i + 1] - CAL_TIME_US[i]);
      return CAL_R_US2[i] + fraction * (CAL_R_US2[i + 1] - CAL_R_US2[i]);
    }
  }
  return CAL_R_US2[N_CAL - 1];
}

unsigned long measureEchoTime() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  return pulseIn(ECHO_PIN, HIGH, ECHO_TIMEOUT_US);
}

unsigned long medianOfThree(unsigned long a, unsigned long b, unsigned long c) {
  if (a > b) { unsigned long v = a; a = b; b = v; }
  if (b > c) { unsigned long v = b; b = c; c = v; }
  if (a > b) { unsigned long v = a; a = b; b = v; }
  return b;
}

void printEstimate() {
  const float distanceMm = MM_PER_US * xUs + OFFSET_MM;
  Serial.print(distanceMm, 2);
  Serial.print(F(", "));
  Serial.println(PUs2, 2);   // TIME variance [us^2], as required for 1.1
}

void finishMeasurement() {
  finished = true;                      // No more measurement lines
  const unsigned long elapsedMs = millis() - startMillis;
  Serial.println(elapsedMs);           // Only the elapsed milliseconds on final line

  for (byte i = 0; i < 3; i++) {       // Visible convergence indication
    digitalWrite(LED_PIN, HIGH);
    delay(90);
    digitalWrite(LED_PIN, LOW);
    delay(90);
  }
}

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(115200);
  Serial.println(F("START"));
  startMillis = millis();
}

void loop() {
  if (finished) return;

  unsigned long now = millis();
  if (!firstPing && (now - lastPingMillis < PING_INTERVAL_MS)) return;
  firstPing = false;
  lastPingMillis = now;

  const unsigned long echoUs = measureEchoTime();
  if (echoUs < MIN_ECHO_US || echoUs > MAX_ECHO_US) return;

  if (!kalmanReady) {
    // A median of three keeps an isolated false echo from setting the initial state.
    startupEchoes[startupCount++] = echoUs;
    if (startupCount < 3) return;

    xUs = (float)medianOfThree(startupEchoes[0], startupEchoes[1], startupEchoes[2]);
    PUs2 = measurementVariance(xUs);
    previousDistanceMm = MM_PER_US * xUs + OFFSET_MM;
    kalmanReady = true;
    printEstimate();
    return;
  }

  const float RUs2 = measurementVariance(xUs);
  const float innovationUs = (float)echoUs - xUs;
  float rejectLimitUs = 6.0f * sqrtf(RUs2);
  if (rejectLimitUs < 60.0f) rejectLimitUs = 60.0f;
  if (fabsf(innovationUs) > rejectLimitUs) return; // Ignore probable false echoes

  // Kalman prediction and measurement update in echo-time units.
  PUs2 += Q_US2;
  const float K = PUs2 / (PUs2 + RUs2);
  xUs += K * innovationUs;
  PUs2 *= (1.0f - K);

  const float distanceMm = MM_PER_US * xUs + OFFSET_MM;
  printEstimate();

  if (PUs2 <= CONVERGED_P_US2 &&
      fabsf(distanceMm - previousDistanceMm) <= MAX_CHANGE_MM) {
    stableUpdates++;
  } else {
    stableUpdates = 0;
  }
  previousDistanceMm = distanceMm;

  if (stableUpdates >= STABLE_UPDATES_REQUIRED) {
    finishMeasurement();
  }
}
