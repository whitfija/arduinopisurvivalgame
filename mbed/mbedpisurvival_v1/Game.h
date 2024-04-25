#ifndef GAME_H
#define GAME_H

#include "Pixel.h"
#include <Arduino.h>
#include "Constants.h"

class Game {
  public:
    int width;
    int height;
    int score;
    int health;
    int timeElapsed;
    Pixel** grid; // pointer instead of actual array for memory reasons

    Game(int gameWidth, int gameHeight);
    void updateGameState();
    void Game::updatePixel(int x, int y, const char* newColor);
    void sendPixelUpdate(int x, int y, const char* color);
    void tick();
    ~Game();
};

#endif