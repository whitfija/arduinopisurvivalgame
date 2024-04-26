#include "Constants.h"
#include "Player.h"
#include "Game.h"
#include "Pixel.h"

/* -------------------- io pins -------------------- */
// joystick
const int xPin = A0;
const int yPin = A1;
const int swPin = 2;

// buttons
const int thrustPin = 3;

/* -------------------- game setup -------------------- */
Game game(GRID_WIDTH, GRID_HEIGHT);
Player player(GRID_WIDTH / 2, GRID_HEIGHT / 2);
int previousDirection = DIRECTION_UP;

/* -------------------- inputs -------------------- */
void readJoystick() {
  bool update = false;
  int xValue = analogRead(xPin);
  int yValue = analogRead(yPin);
  int newDirection = calculateDirection(xValue, yValue);

  if (newDirection != player.direction && newDirection != DIRECTION_CENTER) {
    previousDirection = player.direction;
    printPlayer(false); // clear
    player.updateDirection(newDirection);
    update = true;
  }

  if (update) {
    printPlayer(true);
  }
}

// calculate and return direction based on joystick position
int calculateDirection(int xValue, int yValue) {
  int xRange = 1023 / 3;
  int yRange = 1023 / 3;

  if (yValue < yRange) {
    if (xValue < xRange) return DIRECTION_UP_RIGHT;
    else if (xValue > 2 * xRange) return DIRECTION_DOWN_RIGHT;
    else return DIRECTION_RIGHT;
  } else if (yValue > 2 * yRange) {
    if (xValue < xRange) return DIRECTION_UP_LEFT;
    else if (xValue > 2 * xRange) return DIRECTION_DOWN_LEFT;
    else return DIRECTION_LEFT;
  } else {
    if (xValue < xRange) return DIRECTION_UP; 
    else if (xValue > 2 * xRange) return DIRECTION_DOWN;
    else return DIRECTION_CENTER;
  }
}

void checkButtons() {
  if (digitalRead(thrustPin) == 0) {
    player.thrust();
  }
}

/* -------------------- player display -------------------- */

// print the player pixel art
void printPlayer(bool show) {
  char pixelsToUpdate[13*28];
  int startX = player.x - PLAYER_SIZE / 2;
  int startY = player.y - PLAYER_SIZE / 2;
  pixelsToUpdate[0] = '\0';
  int (*playerArt)[PLAYER_SIZE][PLAYER_SIZE] = player.getArt();
  //int (*playerArt)[PLAYER_SIZE][PLAYER_SIZE] = &playerArtRight;
  for (int i = 0; i < PLAYER_SIZE; ++i) {
    for (int j = 0; j < PLAYER_SIZE; ++j) {
      //if (player.getArt()[j][i] == 1) {
      if ((*playerArt)[j][i] == 1) {
        char pixelUpdate[28];
        if (!show) { // clear
          sprintf(pixelUpdate, "PIXEL,%d,%d,0-0-0\n", startX + i, startY + j);
        } else { // show
          sprintf(pixelUpdate, "PIXEL,%d,%d,0-255-0\n", startX + i, startY + j);
        }
        strcat(pixelsToUpdate, pixelUpdate);
      }
    }
  }
  pixelsToUpdate[sizeof(pixelsToUpdate) - 1] = '\0'; // null termination 
  Serial.println(pixelsToUpdate);
  Serial.flush();
}

/* -------------------- running -------------------- */

void setup() {
  pinMode(swPin, INPUT_PULLUP); 
  pinMode(thrustPin, INPUT_PULLUP); 
  Serial.begin(9600);
  delay(100);
  printPlayer(true);
  //Serial.println("setup");
}

void loop() {
  //Serial.println("hey");
  // inputs
  readJoystick();
  checkButtons();

  // game updates
    // if moving
  if (player.velocityX != 0 or player.velocityY != 0) {
    printPlayer(false);
    player.move();
    player.decelerate();
    printPlayer(true);
  }
    // game timer stuff
  game.tick();
}
