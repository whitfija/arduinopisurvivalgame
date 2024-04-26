#ifndef GAME_H
#define GAME_H

#include "Pixel.h"
#include <Arduino.h>
#include "Constants.h"
#include "Rock.h"
#include "Player.h"

#define MAX_ROCKS 7

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
    bool collision = false;
    int currentRockIndex = 0;

    //Pixel** grid; // pointer instead of actual array for memory reasons

    Game(int gameWidth, int gameHeight);
    void spawnRock();
    void printRock(int index, bool show);
    void removeRock(int index);
    void moveNextRock(int playerX, int playerY);
    void updateGameState();
    void updatePixel(int x, int y, const char* newColor);
    void sendPixelUpdate(int x, int y, const char* color);
    void tick(int playerX, int playerY);
    void updateStar();
    ~Game();
};

#endif