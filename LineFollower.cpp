#include "LineFollower.h"
#include <PID_v1.h>

// Define motor pins
int MtrL1 = 2;
int MtrL2 = 4;
int MtrR1 = 5;
int MtrR2 = 7;
int ENA = 3;
int ENB = 6;

// Define IR sensor pins
int ir1 = A2;
int ir2 = A3;
int ir3 = A4;

const int LineSenseFL = 10;
const int LineSenseFR = 11;

// Define PID variables
double Setpoint = 0;
double Input, Output;
// 2 20 40
// double Kp = 0.8, Ki = 0.5, Kd = 20; // Adjusted PID constants for smoother control
double Kp = 0.8, Ki = 0.5, Kd = 8; 

PID pid(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

// Define threshold for sensor readings
const int threshold = 200; // Adjust this value according to your sensor and lighting conditions

// Define variable to keep track of last movement
enum Movement { STOPPED, FORWARD, RIGHT, LEFT, RIGHT2, LEFT2 };
Movement lastMovement = STOPPED;

// Constructor
LineFollower::LineFollower() {
  // Constructor code here (if needed)
}

// Initialization function
void LineFollower::init() {
  // Set motor pins as outputs
  pinMode(MtrL1, OUTPUT);
  pinMode(MtrL2, OUTPUT);
  pinMode(MtrR1, OUTPUT);
  pinMode(MtrR2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Set IR sensor pins as inputs
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);

  pinMode(LineSenseFL, INPUT);
  pinMode(LineSenseFR, INPUT);

  // Set initial Setpoint and start PID
  Setpoint = 0; // Lower setpoint for slower speed
  pid.SetMode(AUTOMATIC);

  // Start delay
  delay(3000);

  Serial.begin(9600);
}

// Main execution function
void LineFollower::run() {
   // Read IR sensor values
  int val1 = analogRead(ir1);
  int val2 = analogRead(ir2);
  int val3 = analogRead(ir3);

  int LineTrackFL = digitalRead(LineSenseFL);
  int LineTrackFR = digitalRead(LineSenseFR);

  Serial.print("Sensor 1: ");
  Serial.print(val1);
  Serial.print(" - Sensor 2: ");
  Serial.print(val2);
  Serial.print(" - Sensor 3: ");
  Serial.println(val3);

  // Calculate PID input based on sensor inputs
  Input = val2 - threshold; // Error is the difference between center sensor reading and threshold

  // Compute PID output
  pid.Compute();

  // Adjust motor speeds based on PID output for smoother control
  int leftSpeed = 244 - Output; // Adjust speed to maintain a baseline
  int rightSpeed = 244 + Output; // Adjust speed to maintain a baseline

  // Apply speed limits
  leftSpeed = constrain(leftSpeed, 0, 255);
  rightSpeed = constrain(rightSpeed, 0, 255);

  // Apply motor control
  digitalWrite(MtrL1, leftSpeed > 0 ? HIGH : LOW);
  digitalWrite(MtrL2, leftSpeed < 0 ? HIGH : LOW);
  digitalWrite(MtrR1, rightSpeed > 0 ? HIGH : LOW);
  digitalWrite(MtrR2, rightSpeed < 0 ? HIGH : LOW);

  // Apply PWM to control motor speed
  analogWrite(ENA, abs(leftSpeed));
  analogWrite(ENB, abs(rightSpeed));

  // Implement behavior based on sensor readings and last movement
  if (val1 < threshold && val2 > threshold && val3 < threshold) { // 
    // If only the middle sensor detects, move forward
    Forward();
    lastMovement = FORWARD;
    delay(100);
  } else if (val1 < threshold && val2 > threshold && val3 > threshold) {
    // If only the right sensor detects, move right
    TurnR();
    lastMovement = RIGHT;
    delay(100);
    
  } else if (val1 < threshold && val2 < threshold && val3 > threshold) {
    // If only the right sensor detects, move right
    TurnR();
    lastMovement = RIGHT;
    delay(100);

  }  else if (val1 < threshold && val2 > threshold && val3 > threshold && LineTrackFR == 1) {
    // If only the right sensor detects, move right
    TurnR();
    lastMovement = RIGHT2;
    delay(100);
    
  } else if (val1 < threshold && val2 < threshold && val3 > threshold && LineTrackFR == 1) {
    // If only the right sensor detects, move right
    TurnR();
    lastMovement = RIGHT2;
    delay(100);

  }
  
  else if (val1 > threshold && val2 > threshold && val3 < threshold) {
    // If only the left sensor detects, move left
    TurnL();
    lastMovement = LEFT;
    delay(100);

  } else if (val1 > threshold && val2 < threshold && val3 < threshold ) {
    // If only the left sensor detects, move
    TurnL();
    lastMovement = LEFT;
    delay(100);
  } 
   else if (val1 > threshold && val2 > threshold && val3 < threshold && LineTrackFL == 1) {
    // If only the left sensor detects, move left
    TurnL();
    lastMovement = LEFT2;
    delay(100);

  } else if (val1 > threshold && val2 < threshold && val3 < threshold && LineTrackFL == 1 ) {
    // If only the left sensor detects, move
    TurnL();
    lastMovement = LEFT2;
    delay(100);
  } 
  // else if (val1 > threshold && val2 > threshold && val3 > threshold && LineTrackFL == 1 && LineTrackFR == 1 ) {
  //   // If only the left sensor detects, move
  //   Stp();
  //   lastMovement = STOPPED;
  //   delay(100);

    
  // }
   else if (val1 < threshold && val2 < threshold && val3 < threshold) {
    // If all sensors detect, check last movement
    switch (lastMovement) {
      case FORWARD:
        clockWise();
        delay(100);
        break;
      case RIGHT:
        TurnR();
        break;
      case LEFT:
        TurnL();
        break;
      case RIGHT2:
        clockWise();
        delay(100);
        break;
      case LEFT2:
        counterClockWise();
        delay(100);
      break;
      default:
        Stp();
        break;
    }
  } else {
    // If all sensors do not detect, stop
    Forward();
  }
}

void LineFollower::stop() {
    // Code to stop the LineFollower here
    // For example:
    // Stop the motors or sensors
}