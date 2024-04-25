#ifndef PIXEL_H
#define PIXEL_H

#include <Arduino.h>
#include "Constants.h"

class Pixel {
  public:
    int x;
    int y;
    const char* color;

    Pixel(); // deafult needed for memory alloc
    Pixel(int posX, int posY, const char* initialColor);
    void changeColor(const char* newColor);
};

#endif