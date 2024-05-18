#define BUTTON_PIN 13  // Pin connected to the button

int buttonState = HIGH;  // Current state of the button
int lastButtonState = HIGH;  // Previous state of the button
int mode = 0;  // Current mode of the robot: 0 for line follower, 1 for sumobot, 2 for maze bot


// Include libraries and define variables for each mode
// Include Sumo bot code
#include "SumoBot.h"

// Include Line follower code
#include "LineFollower.h"

// Include Maze-solving bot code
#include "MazeSolver.h"


SumoBot sumoBot; // Create an instance of the SumoBot class

LineFollower lineFollower; // Create an instance of the LineFollower class

// MazeSolver mazeSolver; // Create an instance of the SumoBot class

void setup() {
  // pinMode(MODE_BUTTON_PIN, INPUT_PULLUP); // Set mode button pin as input with internal pull-up resistor
  pinMode(BUTTON_PIN, INPUT);

  // Initialize each mode
  // Initialize Sumo bot
  // sumoBot.init();

  // Initialize Line follower bot
  lineFollower.init();

  // Initialize Maze-solving bot
  // mazeSolver.init();
}

void loop() {
   // Read the state of the button
  buttonState = digitalRead(BUTTON_PIN);

  // Check if the button is clicked
  if (buttonState == LOW && lastButtonState == HIGH) {
    delay(50);  // Debounce delay
    buttonState = digitalRead(BUTTON_PIN);  // Read button state again after debounce delay

    // Check if the button is clicked twice
    if (buttonState == LOW) {
      delay(50);  // Debounce delay
      buttonState = digitalRead(BUTTON_PIN);  // Read button state again after debounce delay

      // Check if the button is clicked twice
      if (buttonState == LOW) {
        mode = (mode + 1) % 3;  // Switch to the next mode (cycle through modes)
      }
    }
  }

  // Update last button state
  lastButtonState = buttonState;

  // Perform actions based on the current mode
  switch (mode) {
    case 0:
    // Sumobot mode
   lineFollower.run();
    break;
    case 1:
    // Line follower mode
    lineFollower.run();
    break;
    case 2:
    // Sumobot mode
  lineFollower.run();
      break;
  }

}
