//Includes the Arduino Stepper Library
#include <Stepper.h>

// Defines the number of steps per rotation
const int stepsPerRevolution = 2038;

// Motor pin definitions
#define motorPin1  3     // IN1 on the ULN2003 driver 1
#define motorPin2  4     // IN2 on the ULN2003 driver 1
#define motorPin3  5     // IN3 on the ULN2003 driver 1
#define motorPin4  6     // IN4 on the ULN2003 driver 1

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, motorPin1, motorPin3, motorPin2, motorPin4);

const float debounceDelay = 100;
const int numInputs = 2;
const int inputPins[2] = {8, 9};
int inputState[] = {0, 0};
int lastInputState[] = {0, 0};
int inputFlags[] = {0, 0};
const int buttonRed = 8;     // the number of the pushbutton pin
const int buttonGreen = 10;      // the number of the LED pin
int buttonRedState = 0;         // variable for reading the pushbutton status
int buttonGreenState = 0;         // variable for reading the pushbutton status
int path = 0;

///////
bool setInputFlags() {
// First, we debounce everything
  unsigned long lastStateChangeTime = 0;
  if (millis() - lastStateChangeTime < debounceDelay)
    return;

// Now we look for state changes
  bool stateChanged = false;
  for (int i = 0; i < numInputs; i++)
  {
    inputState[i] = digitalRead(inputPins[i]);
  
    if (inputState[i] != lastInputState[i])
        {
          stateChanged = true;
          lastInputState[i] = inputState[i];
          inputFlags[i] = inputState[i];
        }
   }

// If anything changed, restart the debounce timer
  if (stateChanged) {
    lastStateChangeTime = millis();
  }

return stateChanged;
}
///////

void setup() {
      //Serial.begin(9600);
      pinMode(buttonGreen, INPUT);
}

void loop() {

//  bool updatePath = setInputFlags();
//
//  if (updatePath) {
//      Serial.print("updatePath: ");
//      Serial.print(updatePath);
//  }
//
//  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
//  if (buttonGreenState == HIGH) {
//    // go up:
//    path = 1;
//  } else {
//    // stop:
//    path = 0;
//  }
//
//  if (buttonRedState == HIGH) {
//    // go down:
//    path = -1;
//  } else {
//    // stop:
//    path = 0;
//  }

      delay(1000);  


  // read the state of the pushbutton value:
  buttonGreenState = digitalRead(buttonGreen);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonGreenState == HIGH) {
      myStepper.setSpeed(15);
      myStepper.step(stepsPerRevolution);
      delay(1000);  
  } else {
    // turn LED off:
      myStepper.setSpeed(10);
      myStepper.step(0);
      delay(1000);  

  }
//
//  myStepper.setSpeed(10);
//  myStepper.step(stepsPerRevolution * path);
//  //delay(1000);
  
  // Rotate CCW quickly at 10 RPM
  //myStepper.setSpeed(10);
  //myStepper.step(-stepsPerRevolution);
  //delay(1000);


  

}
