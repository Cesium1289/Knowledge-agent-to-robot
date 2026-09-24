#pragma once
#include"wumpus_world.hpp"
#include<functional>

namespace wumpus {

enum class Action {
    TURN_LEFT,
    TURN_RIGHT,
    MOVE_FORWARD,
    SHOOT,
    GRAB,
    CLIMB
};

class KnowledgeBase {
public:
    KnowledgeBase();
    void tell(WumpusWorld& world)const;
    void tell(Action action)const;
    Action ask(WumpusWorld& world)const;
};

}  // namespace wumpus
