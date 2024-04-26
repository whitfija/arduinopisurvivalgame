#include "Game.h"

Game::Game(int gameWidth, int gameHeight) {
  width = gameWidth;
  height = gameHeight;
  score = 0;
  health = 100;
  timeElapsed = 0;
  starX = -1;
  starY = -1;
  Serial.println("----");

  /*// init grid of pixels
  grid = new Pixel*[width];
  for (int x = 0; x < width; x++) {
    grid[x] = new Pixel[height];
    for (int y = 0; y < height; y++) {
      grid[x][y] = Pixel(x, y, "0-0-0");
    }
  }*/
}

void Game::tick() {
  timeElapsed = timeElapsed + 1;
  //Serial.println(timeElapsed);

  if (timeElapsed % 1000 == 0) {
    if (numRocks < MAX_ROCKS) {
      spawnRock();
    }
  }

  if (timeElapsed % 100 == 0) {
    // move rocks
    for (int i = 0; i < numRocks; i++) {
      printRock(i, false);
      rocks[i].updatePosition();
      printRock(i, true);
    }
  }

  if (timeElapsed % 300 == 0) {
    updateStar();
  }
}

void Game::updateStar() {
    // clear the previous star
    if (starX != -1 && starY != -1) {
        updatePixel(starX, starY, "0-0-0");
    }

    // rng star
    starX = random(width);
    starY = random(height);
    updatePixel(starX, starY, "255-255-255");
}

void Game::spawnRock() {
  // rng for new rock
  int initialX = random(GRID_WIDTH);
  int initialY = random(GRID_HEIGHT);
  int initialVelocityX = random(-5, 6); 
  int initialVelocityY = random(-5, 6);

  // build rock
  if (numRocks < MAX_ROCKS) {
    rocks[numRocks++] = Rock(initialX, initialY, initialVelocityX, initialVelocityY);
  }
}

void Game::printRock(int index, bool show) {
  Rock& rock = rocks[index];
  // 2x2 grid for rock
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      int pixelX = rock.x + i;
      int pixelY = rock.y + j;
      
      // output to pixel
      if (show) {
        updatePixel(pixelX, pixelY, "139-69-19");
      } else {
        updatePixel(pixelX, pixelY, "0-0-0");
      }
    }
  }
}

void Game::removeRock(int index) {
  // clearrock
  printRock(index, false);

  // shift all rocks after the removed one to the left
  for (int i = index; i < numRocks - 1; i++) {
    rocks[i] = rocks[i + 1];
  }
  numRocks--;

  score += 100;
}

void Game::updateGameState() {
  // update
}

void Game::updatePixel(int x, int y, const char* newColor) {
  // check boundaries
  if (x >= 0 && x < width && y >= 0 && y < height) {
    // update color
    //grid[x][y].changeColor(newColor);
    sendPixelUpdate(x, y, newColor);
  }
}

void Game::sendPixelUpdate(int x, int y, const char* color) {
  // serial send to pi 
  Serial.print("PIXEL,");
  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.print(",");
  Serial.println(color);
}

Game::~Game() {
  // memory cleanup
  for (int x = 0; x < width; x++) {
    //delete[] grid[x];
  }
  //delete[] grid;
}