#include <AccelStepper.h>
#define HALFSTEP 8
#define FULLSTEP 4

// Motor pin definitions
#define motorPin1  3     // IN1 on the ULN2003 driver 1
#define motorPin2  4     // IN2 on the ULN2003 driver 1
#define motorPin3  5     // IN3 on the ULN2003 driver 1
#define motorPin4  6     // IN4 on the ULN2003 driver 1

#define stepsPerRotation 2048
#define curtainExtent 10 // Rotations to get to the other end of the throw

#define downPin 8
#define midPin 9
#define upPin 10

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(FULLSTEP, motorPin1, motorPin3, motorPin2, motorPin4);

// Store control pin states
bool downPinState = LOW;
bool midPinState = LOW;
bool upPinState = LOW;

// Keep track of time since last digital pin check
unsigned long lastExecution = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting.");
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(500.0);
  stepper1.setSpeed(500);
  //stepper1.moveTo(2048);

}//--(end setup )---

void checkPins(){
  lastExecution = millis();
  // Check the state of the control pins, and move to the corresponding position if need be
  downPinState = digitalRead(downPin);
  midPinState = digitalRead(midPin);
  upPinState = digitalRead(upPin);

  // Tell serial what's up
  Serial.print("downPin: ");Serial.print(downPinState);Serial.print(" midPin: ");Serial.print(midPinState);Serial.print(" upPin: ");Serial.println(upPinState);

  if (downPinState == HIGH) {
    // Move to the 'down' position
    Serial.println("Moving DOWN");
    stepper1.moveTo(0);
  } else if (midPinState == HIGH) {
    // Move to the 'middle' position
    Serial.println("Moving MIDDLE");
    stepper1.moveTo(0.5*curtainExtent*stepsPerRotation);
    //Serial.println(0.5*curtainExtent*stepsPerRotation);
  } else if (upPinState == HIGH) {
    // Move to the 'up' position
    Serial.println("Moving HIGH");
    stepper1.moveTo(curtainExtent*stepsPerRotation);
  }
  /*
  //Change direction when the stepper reaches the target position
  if (stepper1.distanceToGo() == 0) {
    stepper1.moveTo(-stepper1.currentPosition());
  }
  */

  // Check if the stepper is finished, and if so, turn off the pins
  if (stepper1.distanceToGo() == 0) {
    // Quit trying to set fire to my windows!
    stepper1.disableOutputs();
  }
}
void loop() {
  if (millis() >= (lastExecution + 1000)){
    // If it's been over a second since last run
    checkPins();
  }
  stepper1.run();
  //delay(1000);
}
