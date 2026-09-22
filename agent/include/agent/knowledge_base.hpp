#pragma once
#include"wumpus_world.hpp"

namespace wumpus {

class KnowledgeBase {
public:
    KnowledgeBase();
    void tell(WumpusWorld& world)const;
    void ask(WumpusWorld& world)const;
};

}  // namespace wumpus
