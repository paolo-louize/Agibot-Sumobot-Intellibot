#include "SumoBot.h"
#include <Ultrasonic.h>

// Ultrasonic sensor
Ultrasonic USsense(A0, A1);

// Sensor pins
const int LineSenseFL = 10;
const int LineSenseFR = 11;
const int LineSenseBL = 19;
const int LineSenseBR = 12;

const int ir1 = A2; 
const int ir2 = A3;
const int ir3 = A4;

const int ProxL = 8;
const int ProxR = 9;

// Motor control pins
const int ENA = 3;
const int MtrL1 = 2;
const int MtrL2 = 4;
const int MtrR1 = 5;
const int MtrR2 = 7;
const int ENB = 6;

// Other variables
int LineTrackFL, LineTrackFR, LineTrackBL, LineTrackBR;
int PrxL, PrxR;
int USsenseDst;
const int threshold = 200;

// Constructor
SumoBot::SumoBot() {
  // Constructor code here (if needed)
}

// Initialization function
void SumoBot::init() {
  pinMode(LineSenseFL, INPUT);
  pinMode(LineSenseFR, INPUT);
  pinMode(LineSenseBL, INPUT);
  pinMode(LineSenseBR, INPUT);
  pinMode(ProxL, INPUT);
  pinMode(ProxR, INPUT);
  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);
  pinMode(ENA, OUTPUT);
  pinMode(MtrL1, OUTPUT);
  pinMode(MtrL2, OUTPUT);
  pinMode(MtrR1, OUTPUT);
  pinMode(MtrR2, OUTPUT);
  pinMode(ENB, OUTPUT);
  Serial.begin(9600);
  delay(5000);
  ClockWise();
  delay(2550);
}

// Main execution function
void SumoBot::run() {
  int val1 = analogRead(ir1);
  int val2 = analogRead(ir2);
  int val3 = analogRead(ir3);
  USsenseDst = USsense.read(CM);
  if (USsenseDst > 60) {
    USsenseDst = 0;
  }

  LineTrackFL = digitalRead(LineSenseFL);
  LineTrackFR = digitalRead(LineSenseFR);
  LineTrackBL = digitalRead(LineSenseBL);
  LineTrackBR = digitalRead(LineSenseBR);
  PrxL = digitalRead(ProxL);
  PrxR = digitalRead(ProxR);

  if (LineTrackFL == 0 && LineTrackFR == 0 && LineTrackBL == 0 && LineTrackBR == 0) {
    Stp();
    Serial.println("Stop");
  } else if (LineTrackFL == 0 && LineTrackFR == 0) {
    Backward();
    delay(300);
    Serial.println("Backward");
  } else if (LineTrackBL == 0 && LineTrackBR == 0) {
    Forward();
    delay(1000);
    Serial.println("Forward");
  } else if (LineTrackFL == 0) {
    Backward();
    delay(800);
    TurnL();
    delay(300);
    Serial.println("Backward Left");
  } else if (LineTrackFR == 0) {
    Backward();
    delay(800);
    TurnR();
    delay(500);
    Serial.println("Backward Right");
  } else if (LineTrackBL == 0) {
    TurnR();
    Serial.println("Forward Right");
  } else if (LineTrackBR == 0) {
    TurnL();
    Serial.println("Forward Left");
  } else if (PrxL == 0) {
    ClockWise();
    delay(1200);
    Serial.println("Clockwise");
  } else if (PrxR == 0) {
    CounterClockWise();
    delay(1200);
    Serial.println("Counter Clockwise");
  } else if (USsenseDst > 0) {
    Atk();
    Serial.println("Attack");
  } else if (val1 < threshold && val2 < threshold && val3 < threshold) {
    Backward();
    delay(300);
    ClockWise();
    delay(800);
    Serial.println("LTBACKWARD");
  } else {
    Forward();
    Serial.println("No Sense");
  }
}

void SumoBot::stop() {
    // Code to stop the SumoBot here
    // For example:
    // Stop the motors
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
}
