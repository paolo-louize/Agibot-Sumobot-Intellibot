#ifndef LineFollower_h
#define LineFollower_h

#include <Arduino.h> // Include the Arduino core library for data types and functions

class LineFollower {
public:
  // Constructor
  LineFollower();

  // Function prototypes
  void init(); // Initialization function
  void run(); // Main execution function
  void stop();

  // Add your other function prototypes here

//START Func
void Forward() {
  // Set motor speeds for forward movement at minimum speed
  digitalWrite(MtrL1, LOW);
  digitalWrite(MtrL2, HIGH); //L FORWARD
  digitalWrite(MtrR1, LOW);
  digitalWrite(MtrR2, HIGH); //R FORWARD
  // Apply PWM to control motor speed
  analogWrite(ENA, 180); // Adjust speed as necessary
  analogWrite(ENB, 180); // Adjust speed as necessary
}

void TurnR() {
  // Set motor speeds for right turn at minimum speed
  digitalWrite(MtrL1, LOW);
  digitalWrite(MtrL2, HIGH); //L FORWARD
  digitalWrite(MtrR1, HIGH); //R BACKWARD
  digitalWrite(MtrR2, LOW);
  // Apply PWM to control motor speed
  analogWrite(ENA, 100); // Adjust speed as necessary
  analogWrite(ENB, 80); // Adjust speed as necessary
}

void TurnL() {
  // Set motor speeds for left turn at minimum speed
  digitalWrite(MtrL1, HIGH); //L BACKWARD
  digitalWrite(MtrL2, LOW);
  digitalWrite(MtrR1, LOW);
  digitalWrite(MtrR2, HIGH); //R FORWARD
  // Apply PWM to control motor speed
  analogWrite(ENA, 100); // Adjust speed as necessary
  analogWrite(ENB, 80); // Adjust speed as necessary
}

void Stp() {
  // Stop both motors
  digitalWrite(MtrL1, LOW);
  digitalWrite(MtrL2, LOW);
  digitalWrite(MtrR1, LOW);
  digitalWrite(MtrR2, LOW);
}

void clockWise() {
  // Stop both motors
  digitalWrite(MtrL1, HIGH);
  digitalWrite(MtrL2, LOW);
  digitalWrite(MtrR1, LOW);
  digitalWrite(MtrR2, HIGH);
  analogWrite(ENA, 100); // Adjust speed as necessary
  analogWrite(ENB, 100); // Adjust speed as necessary
}

void counterClockWise() {
  // Stop both motors
  digitalWrite(MtrL1, LOW);
  digitalWrite(MtrL2, HIGH);
  digitalWrite(MtrR1, HIGH);
  digitalWrite(MtrR2, LOW);
  analogWrite(ENA, 100); // Adjust speed as necessary
  analogWrite(ENB, 100); // Adjust speed as necessary
}
//END Func

private:
  // Pin constants
  const int ENA = 3;
  const int MtrL1 = 2;
  const int MtrL2 = 4;
  const int MtrR1 = 5;
  const int MtrR2 = 7;
  const int ENB = 6;

  // Add your private variables and helper functions here
};

#endif
