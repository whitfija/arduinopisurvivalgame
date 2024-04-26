#ifndef PLAYER_H
#define PLAYER_H

#include <Arduino.h>
#include "Constants.h"

class Player {
  public:
    int x;
    int y;
    int direction;
    int velocityX;
    int velocityY;
    static const int MAX_VELOCITY = 30;
    static const int MIN_VELOCITY = -30;
    static const int decelerationRate = 1;
    static const int thrustRate = 3;

    Player(int initialX, int initialY);
    void changePosition(int newX, int newY);
    void updateDirection(int newDirection);
    void moveForward(int steps);
    int (*getArt())[PLAYER_SIZE][PLAYER_SIZE];
    void thrust();
    void decelerate();
    bool move();
};

#endif