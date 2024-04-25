#include "Game.h"

Game::Game(int gameWidth, int gameHeight) {
  width = gameWidth;
  height = gameHeight;
  score = 0;
  health = 100;
  timeElapsed = 0;
  Serial.println("----");

  // init grid of pixels
  grid = new Pixel*[width];
  for (int x = 0; x < width; x++) {
    grid[x] = new Pixel[height];
    for (int y = 0; y < height; y++) {
      grid[x][y] = Pixel(x, y, "0-0-0");
    }
  }
  //Serial.println("hello 2");
}

void Game::tick() {
  timeElapsed = timeElapsed + 1;
}


void Game::updateGameState() {
  // update
}

void Game::updatePixel(int x, int y, const char* newColor) {
  // check boundaries
  if (x >= 0 && x < width && y >= 0 && y < height) {
    // update color
    grid[x][y].changeColor(newColor);
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
    delete[] grid[x];
  }
  delete[] grid;
}