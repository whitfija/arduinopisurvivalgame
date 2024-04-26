#include "Constants.h"
#include "Player.h"
#include "Game.h"
#include "Pixel.h"
#include <LiquidCrystal.h>

/* -------------------- io pins -------------------- */
// joystick
const int xPin = A0;
const int yPin = A1;
const int swPin = 2;

// buttons
const int thrustPin = 3;
const int firePin = 5;

/*// lcd
#define LCD_RS  A8
#define LCD_EN  A9
#define LCD_D4  A10
#define LCD_D5  A11
#define LCD_D6  A12
#define LCD_D7  A13
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
*/

/* -------------------- game setup -------------------- */
Game game(GRID_WIDTH, GRID_HEIGHT);
Player player(GRID_WIDTH / 2, GRID_HEIGHT / 2);
int previousDirection = DIRECTION_UP;

bool running = false;
bool notStarted = true;

void resetGame() {
  // clear
    // rock
  for (int i = 0; i < game.numRocks; i++) {
    game.printRock(i, false);
  }
    // star
  game.sendPixelUpdate(game.starX, game.starY, "0-0-0");

  running = false;
  notStarted = true;
  int previousDirection = DIRECTION_UP;
  player = Player(GRID_WIDTH / 2, GRID_HEIGHT / 2);
  game = Game(GRID_WIDTH, GRID_HEIGHT);
}

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

  if (digitalRead(firePin) == 0) {
    fire();
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
  for (int i = 0; i < PLAYER_SIZE; ++i) {
    for (int j = 0; j < PLAYER_SIZE; ++j) {
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
  game.tick(player.x, player.y);
  Serial.println(pixelsToUpdate);
  //Serial.flush();
}

// player firing
void fire() {
  int posX = player.x;
  int posY = player.y;
  int dirX = 0;
  int dirY = 0;

  switch (player.direction) {
    case DIRECTION_UP:
      dirY = -1;
      break;
    case DIRECTION_DOWN:
      dirY = 1;
      break;
    case DIRECTION_LEFT:
      dirX = -1;
      break;
    case DIRECTION_RIGHT:
      dirX = 1;
      break;
    case DIRECTION_UP_LEFT:
      dirX = -1;
      dirY = -1;
      break;
    case DIRECTION_UP_RIGHT:
      dirX = 1;
      dirY = -1;
      break;
    case DIRECTION_DOWN_LEFT:
      dirX = -1;
      dirY = 1;
      break;
    case DIRECTION_DOWN_RIGHT:
      dirX = 1;
      dirY = 1;
      break;
    default:
      break;
  }

  int stepCounter = 0;
  while (posX >= 0 && posX < GRID_WIDTH && posY >= 0 && posY < GRID_HEIGHT) {
    // check if fire hit rock
    for (int i = 0; i < game.numRocks; i++) {
      Rock& rock = game.rocks[i];
      int distanceX = abs(rock.x - posX);
      int distanceY = abs(rock.y - posY);
      if (distanceX <= 2 && distanceY <= 2) {
        // hit
        // remove the rock from the array
        game.removeRock(i);
        break;
      }
    }

    // print the laser pixel
    if (stepCounter % 2 == 0) {
      char pixelUpdate[28];
      sprintf(pixelUpdate, "PIXEL,%d,%d,255-0-0\n", posX, posY);
      Serial.println(pixelUpdate);
    }

    // move the laser one step
    posX += dirX;
    posY += dirY;
    stepCounter++;
  }

  // clear the laser path
  posX = player.x;
  posY = player.y;
  stepCounter = 0;
  while (posX >= 0 && posX < GRID_WIDTH && posY >= 0 && posY < GRID_HEIGHT) {
    if (stepCounter % 2 == 0) {
      char pixelUpdate[28];
      sprintf(pixelUpdate, "PIXEL,%d,%d,0-0-0\n", posX, posY);
      Serial.println(pixelUpdate);
    }
    posX += dirX;
    posY += dirY;
    stepCounter++;
  }
}

/* -------------------- running -------------------- */

void setup() {
  // inputs
  pinMode(swPin, INPUT_PULLUP); 
  pinMode(thrustPin, INPUT_PULLUP); 
  pinMode(firePin, INPUT_PULLUP);

  // output
  // lcd
  //lcd.begin(16, 2);
  //lcd.print("hello, world!");

  Serial.begin(9600);
  delay(100);
  //printPlayer(true);
  //Serial.println("setup");
}

void loop() {
  /** gameplay **/
  while (running) {
    //lcd.begin(16, 2);
    //lcd.print("hello, world!");

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
    game.tick(player.x, player.y);

    if (game.collision) {
      running = false;
    }
  }

  if(notStarted) {
    // game hasnt started, waiting for thrust button
    if (digitalRead(thrustPin) == 0) {
      // startup routine
      notStarted = false;
      running = true;
      printPlayer(true);
      delay(400);
      printPlayer(false);
      delay(400);
      printPlayer(true);
      delay(400);
      printPlayer(false);
      delay(400);
      printPlayer(true);
      delay(1000);
    }
  } else {
    // end game routine
    printPlayer(true);
    delay(400);
    printPlayer(false);
    delay(400);
    printPlayer(true);
    delay(400);
    printPlayer(false);
    delay(400);
    printPlayer(true);
    delay(400);
    printPlayer(false);
    delay(1000);
    resetGame();
  }
}
