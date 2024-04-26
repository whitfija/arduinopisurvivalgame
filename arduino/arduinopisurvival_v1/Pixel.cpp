#include "Pixel.h"

Pixel::Pixel() {

}

Pixel::Pixel(int posX, int posY, const char* initialColor) {
    x = posX;
    y = posY;
    color = initialColor;
}

void Pixel::changeColor(const char* newColor) {
    color = newColor;
}