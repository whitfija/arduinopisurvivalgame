#ifndef GAME_H
#define GAME_H

#include "Pixel.h"
#include <Arduino.h>
#include "Constants.h"
#include "Rock.h"

#define MAX_ROCKS 5

class Game {
  public:
    int width;
    int height;
    int score;
    int health;
    int timeElapsed;

    int starX;
    int starY;

    Rock rocks[MAX_ROCKS];
    int numRocks = 0;

    //Pixel** grid; // pointer instead of actual array for memory reasons

    Game(int gameWidth, int gameHeight);
    void spawnRock();
    void printRock(int index, bool show);
    void removeRock(int index);
    void updateGameState();
    void updatePixel(int x, int y, const char* newColor);
    void sendPixelUpdate(int x, int y, const char* color);
    void tick();
    void updateStar();
    ~Game();
};

#endif