#pragma once
#include"wumpus_world.hpp"
#include<functional>

namespace wumpus {

using Action = std::function<void()>;

class KnowledgeBase {
public:
    KnowledgeBase();
    void tell(WumpusWorld& world)const;
    void tell(Action action)const;
    Action ask(WumpusWorld& world)const;
};

}  // namespace wumpus
