
/*
 Stepper Motor Control - one revolution

 This program drives a unipolar or bipolar stepper motor.
 The motor is attached to digital pins 8 - 11 of the Arduino.

 The motor should revolve one revolution in one direction, then
 one revolution in the other direction.


 Created 11 Mar. 2007
 Modified 30 Nov. 2009
 by Tom Igoe

 */

#include <Stepper.h>

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution of your motor

int currentRotations = 0; // shade starts off fully "down"
int targetPosition = 0;

bool pin7state = LOW;
bool pin6state = LOW;
bool pin5state = LOW;


// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  // Set the right digital pins to input
  pinMode(7, INPUT); // 7 high will be all the way up (9 rotations)
  pinMode(6, INPUT); // 6 will be mid-level (4 rotations)
  pinMode(5, INPUT); // 5 will be down (0 rotations)
  
  // set the speed at 10 rpm:
  myStepper.setSpeed(10);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  pin7state = digitalRead(7);
  pin6state = digitalRead(6);
  pin5state = digitalRead(5);
  
  Serial.print("Pin7: ");Serial.print(pin7state);Serial.print(" Pin6: ");Serial.print(pin6state);Serial.print(" Pin5: ");Serial.println(pin5state);
  
  if(pin7state==HIGH){
    targetPosition = 9;
  } else if (pin6state==HIGH) {
    targetPosition = 4;
  } else if (pin5state==HIGH) {
    targetPosition = 0;
  }
  //targetPosition = analogRead(potPin);
  //targetPosition = map(targetPosition,0,1023,0,9);
  Serial.print("Target: ");Serial.println(targetPosition);
  Serial.print("Moving: ");Serial.println(targetPosition-currentRotations);
  myStepper.step(-1*(targetPosition-currentRotations)*stepsPerRevolution);
  currentRotations=currentRotations+(targetPosition-currentRotations);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  delay(2000);
}

