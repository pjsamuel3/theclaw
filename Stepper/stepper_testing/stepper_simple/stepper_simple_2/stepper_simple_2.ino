#include <Stepper.h>

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
// for your motor


// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 3, 5, 4, 6);

int stepCount = 0;  // number of steps the motor has taken

void setup() {
  // nothing to do inside the setup

}

void loop() {
  // read the sensor value:
  int sensorReading = analogRead(A0);

  sensorReading = sensorReading + 20;
  // map it to a range from 0 to 100:
  int motorSpeed = map(sensorReading, 0, 1023, 15, -15);

  
  // set the motor speed:
  if (motorSpeed > 1) {
    myStepper.setSpeed(motorSpeed);
    // step 1/100 of a revolution:
    myStepper.step(stepsPerRevolution / 100);
  }

  if (motorSpeed < 0) {
    myStepper.setSpeed(-motorSpeed);
    // step 1/100 of a revolution:
    myStepper.step(-stepsPerRevolution / 100);
  }


}
