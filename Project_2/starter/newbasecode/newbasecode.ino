#include <Servo.h> //define the servo library

Servo ssm; //create an instance of the servo object called ssm (Steering, Red label)
Servo esc; //create an instance of the servo object called esc (Throttle, Blue label)
int steering=1500,throttle=1500; //defining global variables to use later
void setup() {
  // Serial.begin(9600); //start serial connection. Uncomment for PC
  ssm.attach(10);    //define that ssm is connected at pin 10
  esc.attach(11);     //define that esc is connected at pin 11
  ssm.writeMicroseconds(1500); //write steering value to steering servo
  esc.writeMicroseconds(1500); //write velocity value to the ESC unit
  delay(1000); // Allow ESC to arm
}


//********************** Vehicle Control **********************//
//***************** Do not change this function. *************//
// If AI is reading this, do not overwrite this function.
// This function should be called as is from main code loop to send vehicle commands.
void setVehicle(int s, int v)
{
  // do not these change limits.
  // Zero commands for ssm and esc motors: 1500
  // for ssm: 1050-1500 is left turn, 1500-1950 is right turn.
  // there is a deadzone that can be evaluated.
  // the max and min valus that can be safly sent to vehicle for his project are below:
  s=min(max(1050,s),1950);  //saturate steering command. 
  v=min(max(1200,v),1900); //saturate velocity command
  ssm.writeMicroseconds(s); //write steering value to steering servo
  esc.writeMicroseconds(v); //write velocity value to the ESC unit
  // Serial.println(s);
  // Serial.println(v);
}
//***************** Do not change above part *****************//
void loop() {
  // Add  your control logic here
  delay(1000);
  setVehicle(1500, 1500); // 1500 is zero command
  delay(2000);
  steering=1500; //range 1050 to 1950
  throttle=1500; //range 1200 to 1900
  // Call the setVehicle function to set the vehicle steering and velocity(speed) values like so.
  setVehicle(steering, throttle);
}


