#ifndef CONSTANTS_H
#define CONSTANTS_H

const int GRID_WIDTH = 95;
const int GRID_HEIGHT = 64;

const int DIRECTION_CENTER = 0;
const int DIRECTION_UP = 1;
const int DIRECTION_UP_RIGHT = 2;
const int DIRECTION_RIGHT = 3;
const int DIRECTION_DOWN_RIGHT = 4;
const int DIRECTION_DOWN = 5;
const int DIRECTION_DOWN_LEFT = 6;
const int DIRECTION_LEFT = 7;
const int DIRECTION_UP_LEFT = 8;

/** player stuff **/
const int PLAYER_SIZE = 4;
const int playerArtUp[PLAYER_SIZE][PLAYER_SIZE] = {
  {0, 0, 0, 0},
  {0, 1, 1, 0},
  {1, 1, 1, 1},
  {0, 0, 0, 0},
};
const int playerArtDown[PLAYER_SIZE][PLAYER_SIZE] = {
  {0, 0, 0, 0},
  {1, 1, 1, 1},
  {0, 1, 1, 0},
  {0, 0, 0, 0},
};
const int playerArtLeft[PLAYER_SIZE][PLAYER_SIZE] = {
  {0, 0, 1, 0},
  {0, 1, 1, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 0},
};
const int playerArtRight[PLAYER_SIZE][PLAYER_SIZE] = {
  {0, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 1, 1, 0},
  {0, 1, 0, 0},
};
const int playerArtUpLeft[PLAYER_SIZE][PLAYER_SIZE] = {
  {0, 0, 1, 1},
  {0, 1, 1, 0},
  {1, 1, 0, 0},
  {1, 0, 0, 0},
};
const int playerArtUpRight[PLAYER_SIZE][PLAYER_SIZE] = {
  {1, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 1},
  {0, 0, 0, 1},
};
const int playerArtDownRight[PLAYER_SIZE][PLAYER_SIZE] = {
  {0, 0, 0, 1},
  {0, 0, 1, 1},
  {0, 1, 1, 0},
  {1, 1, 0, 0},
};
const int playerArtDownLeft[PLAYER_SIZE][PLAYER_SIZE] = {
  {1, 0, 0, 0},
  {1, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 1},
};

#endif