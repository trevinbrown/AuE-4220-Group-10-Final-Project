
const int trigPins[4] = {13, 9, 4, 3};
const int echoPins[4] = {12, 8, 5, 2};

const char* sensorNames[4] = {
  "Front 1",
  "Front 2",
  "Left",
  "Right"
};

const int ledPin = 6;

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < 4; i++) {
    pinMode(trigPins[i], OUTPUT);
    pinMode(echoPins[i], INPUT);
    digitalWrite(trigPins[i], LOW);
  }

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.println("4 SENSOR TEST");
}

float readDistance(int sensor) {
  digitalWrite(trigPins[sensor], LOW);
  delayMicroseconds(2);

  digitalWrite(trigPins[sensor], HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPins[sensor], LOW);

  unsigned long duration = pulseIn(
    echoPins[sensor], HIGH, 15000UL
  );

  if (duration == 0) {
    return -1;
  }

  return duration * 0.1715;
}

void loop() {
  digitalWrite(ledPin, HIGH);

  for (int i = 0; i < 4; i++) {
    float distance = readDistance(i);

    Serial.print(sensorNames[i]);
    Serial.print(": ");

    if (distance < 0) {
      Serial.println("NO ECHO");
    } else {
      Serial.print(distance, 1);
      Serial.println(" mm");
    }

    delay(60);
  }

  digitalWrite(ledPin, LOW);

  Serial.println("--------------------");
  delay(500);
}
