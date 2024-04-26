#ifndef ROCK_H
#define ROCK_H

#include <Arduino.h>
#include "Constants.h"

class Rock {
  public:
    int x;
    int y;
    int velocityX;
    int velocityY;

    Rock(); // default needed for memory alloc
    Rock(int initialX, int initialY, int initialVelocityX, int initialVelocityY);
    void updatePosition();
};

#endif