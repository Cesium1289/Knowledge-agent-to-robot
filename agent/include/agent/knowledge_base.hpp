#pragma once
#include"wumpus_world.hpp"
#include<functional>
#include<set>
#include<map>

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
    void tell(const WumpusWorld& world);
    void tell(const Action& action);
    Action ask(const WumpusWorld& world);

private:
    std::pair<int,int> believed_location = {1, 1};
    std::string believed_direction = "East";

    std::set<std::pair<int,int>> visited;
    std::map<std::pair<int,int>, WumpusWorld::PerceptResult> known_percepts;
    std::set<std::pair<int,int>> known_safe;
    Action action_toward(std::pair<int,int>target)const;

};

}  // namespace wumpus
