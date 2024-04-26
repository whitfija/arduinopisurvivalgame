#include "Player.h"

Player::Player(int initialX, int initialY) {
    x = initialX;
    y = initialY;
    direction = DIRECTION_UP;
    velocityX = 0;
    velocityY = 0;
}

void Player::updateDirection(int newDirection) {
  direction = newDirection;
}

/** movement **/

void Player::changePosition(int newX, int newY) {
    x = newX;
    y = newY;
}

void Player::thrust() {
    switch (direction) {
        case DIRECTION_UP:
          velocityY -= thrustRate;
          break;
        case DIRECTION_DOWN:
          velocityY += thrustRate;
          break;
        case DIRECTION_LEFT:
          velocityX -= thrustRate;
          break;
        case DIRECTION_RIGHT:
          velocityX += thrustRate;
          break;
        case DIRECTION_UP_LEFT:
          velocityY -= thrustRate;
          velocityX -= thrustRate;
          break;
        case DIRECTION_UP_RIGHT:
          velocityY -= thrustRate;
          velocityX += thrustRate;
          break;
        case DIRECTION_DOWN_LEFT:
          velocityY += thrustRate;
          velocityX -= thrustRate;
          break;
        case DIRECTION_DOWN_RIGHT:
          velocityY += thrustRate;
          velocityX += thrustRate;
          break;
        default:
            break;
    }

    velocityX = constrain(velocityX, MIN_VELOCITY, MAX_VELOCITY);
    velocityY = constrain(velocityY, MIN_VELOCITY, MAX_VELOCITY);
}

void Player::decelerate() {
  if (velocityX != 0) {
      velocityX -= (velocityX > 0) ? decelerationRate : -decelerationRate;
      if (abs(velocityX) <= 1) {
          velocityX = 0;
      }
  }
  if (velocityY != 0) {
      velocityY -= (velocityY > 0) ? decelerationRate : -decelerationRate;
      if (abs(velocityY) <= 1) {
          velocityY = 0;
      }
  }
}

// true if moved
bool Player::move() {
    int prevX = x;
    int prevY = y;

    // move the player based on velocity
    x += velocityX / 2;
    y += velocityY / 2;

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

    if (x != prevX || y != prevY) {
        return true; // moved
    } else {
        return false; // did not move
    }
}

void Player::moveForward(int steps) {
  switch (direction) {
    case DIRECTION_UP:
      if (y > 0) y = y - steps;
      break;
    case DIRECTION_DOWN:
      if (y < GRID_HEIGHT - 1) y = y + steps;
      break;
    case DIRECTION_LEFT:
      if (x > 0) x = x - steps;
      break;
    case DIRECTION_RIGHT:
      if (x < GRID_WIDTH - 1) x = x + steps;
      break;
    case DIRECTION_UP_LEFT:
      if (x > 0 && y > 0) {
        x = x - steps;
        y = y - steps;
      }
      break;
    case DIRECTION_UP_RIGHT:
      if (x < GRID_WIDTH - 1 && y > 0) {
        x = x + steps;
        y = y - steps;
      }
      break;
    case DIRECTION_DOWN_LEFT:
      if (x > 0 && y < GRID_HEIGHT - 1) {
        x = x - steps;
        y = y + steps;
      }
      break;
    case DIRECTION_DOWN_RIGHT:
      if (x < GRID_WIDTH - 1 && y < GRID_HEIGHT - 1) {
        x = x + steps;
        y = y + steps;
      }
      break;
    default:
      break;
  }
}

/** art **/

int (*Player::getArt())[PLAYER_SIZE][PLAYER_SIZE] {
  
  const int (*up)[PLAYER_SIZE][PLAYER_SIZE] = &playerArtUp;
  const int (*down)[PLAYER_SIZE][PLAYER_SIZE] = &playerArtDown; 
  const int (*left)[PLAYER_SIZE][PLAYER_SIZE] = &playerArtLeft; 
  const int (*right)[PLAYER_SIZE][PLAYER_SIZE] = &playerArtRight; 
  const int (*upleft)[PLAYER_SIZE][PLAYER_SIZE] = &playerArtUpLeft; 
  const int (*downleft)[PLAYER_SIZE][PLAYER_SIZE] = &playerArtDownLeft; 
  const int (*upright)[PLAYER_SIZE][PLAYER_SIZE] = &playerArtUpRight; 
  const int (*downright)[PLAYER_SIZE][PLAYER_SIZE] = &playerArtDownRight; 

  const int (*art)[PLAYER_SIZE][PLAYER_SIZE];
  art = up;

  if (direction == DIRECTION_UP) {
    //Serial.println("return up");
    art = up;
    return up;
  } 
  if (direction == DIRECTION_DOWN) {
    //Serial.println("return down");
    art = down;
    return down;
  } 
  if (direction == DIRECTION_LEFT) {
    //Serial.println("return left");
    art = left;
    return left;
  } 
  if (direction == DIRECTION_RIGHT) {
    //Serial.println("return right");
    art = right;
    return right;
  } 
  if (direction == DIRECTION_UP_LEFT) {
    //Serial.println("return upleft");
    art = upleft;
    return upleft;
  } 
  if (direction == DIRECTION_UP_RIGHT) {
    //Serial.println("return upright");
    art = upright;
    return upright;
  } 
  if (direction == DIRECTION_DOWN_LEFT) {
    //Serial.println("return downleft");
    art = downleft;
    return downleft;
  } 
  if (direction == DIRECTION_DOWN_RIGHT) {
    //Serial.println("return downright");
    art = downright;
    return downright;
  }

  return up;
}