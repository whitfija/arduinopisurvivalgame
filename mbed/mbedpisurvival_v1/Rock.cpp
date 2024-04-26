#include "rock.h"

Rock::Rock() {

}

Rock::Rock(int initialX, int initialY, int initialVelocityX, int initialVelocityY) {
    x = initialX;
    y = initialY;
    velocityX = initialVelocityX;
    velocityY = initialVelocityY;
}

void Rock::updatePosition() {
    x += velocityX;
    y += velocityY;

    // wraparound
    if (x < 0) {
        x = GRID_WIDTH - 1;
    } else if (x >= GRID_WIDTH) {
        x = 0;
    }
    if (y < 0) {
        y = GRID_HEIGHT - 1;
    } else if (y >= GRID_HEIGHT) {
        y = 0;
    }
}