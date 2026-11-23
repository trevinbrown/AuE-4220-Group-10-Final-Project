#define trigPin 13 //Trig to Arduino pin 13
#define echoPin 12 //Echo to Arduino pin 12
void setup() {
Serial.begin (9600); //Serial communications at 9600 bps
pinMode(trigPin, OUTPUT); //Set the trigPin as output
pinMode(echoPin, INPUT); //Set the echoPin as input
}
void loop() {
float time, distance;
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
time = pulseIn(echoPin, HIGH);
Serial.print(time);
Serial.println(" μs");
delay(100);
}
