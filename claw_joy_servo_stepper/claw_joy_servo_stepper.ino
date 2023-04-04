#include <Stepper.h>
#include <Servo.h>


// Motor pin definitions
#define motorPin1  3      // IN1 on the ULN2003 driver 1
#define motorPin2  4      // IN2 on the ULN2003 driver 1
#define motorPin3  5      // IN3 on the ULN2003 driver 1
#define motorPin4  6      // IN4 on the ULN2003 driver 1

#define joystickButtonPin  8 // Joystick Button Pin
#define servoClawPin  9   // Servo Pin

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, motorPin1, motorPin3, motorPin2, motorPin4);

Servo clawServo;

int xAxisValue = 0;
int yAxisValue = 0;
bool buttonIsDown = false;

void setup() {

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(joystickButtonPin, INPUT_PULLUP); //set pin 8 as an input and enable the internal pull-up resistor
  
  Serial.begin(9600);
  
  
  clawServo.attach(servoClawPin);  // attaches the servo on pin 9 to the servo object
}

void loop() {


  // Joystick

  xAxisValue = analogRead(A0); // read X axis value [0..1023]
  yAxisValue = analogRead(A1); // read Y axis value [0..1023]
  buttonIsDown = digitalRead(8); // read Button state [0,1]
  Serial.print("X:");
  Serial.print(xAxisValue, DEC);
  Serial.print(" | Y:");
  Serial.print(yAxisValue, DEC);
  Serial.print(" | Button:");
  Serial.print(buttonIsDown, DEC);
//  
  // reads the value of the potentiometer (value between 0 and 1023)
  //int analogValue = analogRead(A0);

  // scales it to use it with the servo (value between 0 and 180)
  int clawAngle = map(yAxisValue, 0, 1023, 0, 180);

  clawAngle = clawAngle + 2; //Calibrate
  Serial.print(" | clawAngle:");
  Serial.println(clawAngle, DEC);

  // sets the servo position according to the scaled value
  clawServo.write(clawAngle); 

  //Stepper


  xAxisValue = xAxisValue + 28;
  // map it to a range from 0 to 100:
  int motorSpeed = map(xAxisValue, 0, 1023, 18, -18);

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
