#include <AccelStepper.h>
#define HALFSTEP 8

///https://community.element14.com/members-area/personalblogs/b/blog/posts/arduino-controlling-stepper-motor-28byj-48-with-accelstepper-library
///https://42bots.com/tutorials/28byj-48-stepper-motor-with-uln2003-driver-and-arduino-uno/



// Motor pin definitions
#define motorPin1  3     // IN1 on the ULN2003 driver 1
#define motorPin2  4     // IN2 on the ULN2003 driver 1
#define motorPin3  5     // IN3 on the ULN2003 driver 1
#define motorPin4  6     // IN4 on the ULN2003 driver 1

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);

const int buttonRed = 8;     // the number of the pushbutton pin
const int buttonGreen = 9;      // the number of the LED pin
int buttonRedState = 0;         // variable for reading the pushbutton status
int buttonGreenState = 0;         // variable for reading the pushbutton status
int path = 0;                       //Direction of blind (1 = down, 0 = stop, -1 = up)


void setup() {
//  stepper1.setMaxSpeed(2000.0);
//  stepper1.setAcceleration(400.0);
//  stepper1.setSpeed(100);
//  stepper1.moveTo(10000);

}//--(end setup )---

void loop() {

  buttonRedState = digitalRead(buttonRed);
  buttonGreenState = digitalRead(buttonGreen);

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  //if (buttonState == HIGH) {
    // turn LED on:
    //digitalWrite(ledPin, HIGH);
  //} else {
    // turn LED off:
    //digitalWrite(ledPin, LOW);
  //}

  if (path != 0) {
    /*
       Manually running the blind
    */
    //small_stepper.step(ccw ? path : -path);
    //currentPosition = currentPosition + path;
  }

  /*
     After running setup() the motor might still have
     power on some of the coils. This is making sure that
     power is off the first time loop() has been executed
     to avoid heating the stepper motor draining
     unnecessary current
  */
  //if (initLoop) {
    //initLoop = false;
    //stopPowerToCoils();
  //}

//  //Change direction when the stepper reaches the target position
//  if (stepper1.distanceToGo() == 0) {
//    stepper1.moveTo(-stepper1.currentPosition());
//  }
//  stepper1.run();

    if (stepper1.distanceToGo() == 0)
    {
        // Random change to speed, position and acceleration
        // Make sure we dont get 0 speed or accelerations
        delay(100);
        stepper1.moveTo(2000);
        stepper1.setMaxSpeed(1000);
        stepper1.setAcceleration(1000);
    }
    stepper1.run();
}
