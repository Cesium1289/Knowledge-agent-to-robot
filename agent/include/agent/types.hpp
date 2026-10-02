#pragma once
#include<utility>

namespace wumpus{

enum class Action{
    TURN_LEFT,
    TURN_RIGHT,
    MOVE_FORWARD,
    SHOOT,
    GRAB,
    CLIMB
};

enum Direction{
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
};

constexpr int DX[4] = {0,1,0,-1};
constexpr int DY[4] = {1,0,-1,0};

}//namespace wumpus