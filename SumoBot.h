#ifndef SumoBot_h
#define SumoBot_h

#include <Arduino.h> // Include the Arduino core library for data types and functions

class SumoBot {
public:
  // Constructor
  SumoBot();
  

  // Function prototypes
  void init(); // Initialization function
  void run(); // Main execution function
  void stop();

  // Add your other function prototypes here

//START Func
  void Forward(){
    analogWrite(ENA, 255);
    analogWrite(ENB, 255);
    digitalWrite(MtrL1, LOW);
    digitalWrite(MtrL2, HIGH); //L FORWARD
    digitalWrite(MtrR1, LOW);
    digitalWrite(MtrR2, HIGH); //R FORWARD
  }

  void Backward(){
    analogWrite(ENA, 255);
    analogWrite(ENB, 255);
    digitalWrite(MtrL1, HIGH);
    digitalWrite(MtrL2, LOW); //L FORWARD
    digitalWrite(MtrR1, HIGH);
    digitalWrite(MtrR2, LOW); //R FORWARD
  }

  void TurnL(){
    analogWrite(ENA, 150);
    analogWrite(ENB, 255);
    digitalWrite(MtrL1, HIGH); //L BACKWARD
    digitalWrite(MtrL2, LOW);
    digitalWrite(MtrR1, LOW);
    digitalWrite(MtrR2, HIGH); //R FORWARD
  }

  void TurnR(){
    analogWrite(ENA, 255);
    analogWrite(ENB, 150);
    digitalWrite(MtrL1, LOW);
    digitalWrite(MtrL2, HIGH); //L FORWARD
    digitalWrite(MtrR1, HIGH); //R BACKWARD
    digitalWrite(MtrR2, LOW);
  }

  void CounterClockWise(){
    analogWrite(ENA, 255);
    analogWrite(ENB, 255);
    digitalWrite(MtrL1, LOW);
    digitalWrite(MtrL2, HIGH); //L FORWARD
    digitalWrite(MtrR1, HIGH);
    digitalWrite(MtrR2, LOW); //R FORWARD
  }

  void findEnemy(){
    analogWrite(ENA, 255);
    analogWrite(ENB, 230);
    digitalWrite(MtrL1, LOW);
    digitalWrite(MtrL2, HIGH); //L FORWARD
    digitalWrite(MtrR1, HIGH);
    digitalWrite(MtrR2, LOW); //R FORWARD
  }

  void ClockWise(){
    analogWrite(ENA, 255);
    analogWrite(ENB, 255);
    digitalWrite(MtrL1, HIGH);
    digitalWrite(MtrL2, LOW);
    digitalWrite(MtrR1, LOW);
    digitalWrite(MtrR2, HIGH);
  }

  void Atk(){
    analogWrite(ENA, 255);
    analogWrite(ENB, 255);
    digitalWrite(MtrL1, LOW);
    digitalWrite(MtrL2, HIGH); //L FORWARD
    digitalWrite(MtrR1, LOW);
    digitalWrite(MtrR2, HIGH); //R FORWARD
  }

  void Stp(){
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
    digitalWrite(MtrL1, LOW);
    digitalWrite(MtrL2, LOW);
    digitalWrite(MtrR1, LOW);
    digitalWrite(MtrR2, LOW);
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
