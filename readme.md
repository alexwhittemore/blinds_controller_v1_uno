# blinds_controller
This is the component of the project to run on on an Arduino, taking control signals from the ESP8266 component and using them to drive stepper motors.

## Requirements
This project depends on the AccelStepper stepper control library. You can find documentation on the library and how to install it here: http://www.airspayce.com/mikem/arduino/AccelStepper/

## Hardware
The hardware for this half of the project is an Arduino Uno wired to a bank of 28BYJ-48 stepper motors. The stepper driver boards are powered from a 12V supply, while the arduino is powered from a 5V phone charger. The ESP8266 half is powered from Arduino's 5V rail.

Three GPIO pins on the ESP8266 are used to signal the Arduino component, "Down" on D3 (GP0 in the Blynk app), "Mid" on D2 (GP4) and "High" on D1 (GP5). My blinds take 9 full rotatins to go full down to full up, so Down is 0 rotations, Mid is 4.5, and High is 9.

These three pins are wired to Arduino pins 8/9/10 for down, mid, and up. That is, D3-8, D2-9, D1-10.

Additionally, the stepper bank is wired pins 1-4 to Arduino pins 3-6.

## Notes on startup
The Blynk library seems not to assert the state of pins at start until you actuate them in-app. My MO so far has been to plug in my hardware stack holding the Arduino reset button, until I can load the app, wait for the ESP8266 to connect, and let the arduino boot with all pins properly low. I've just included a fix to assert low during startup, but I haven't actually tested it. Try that if things go haywire on startup.
