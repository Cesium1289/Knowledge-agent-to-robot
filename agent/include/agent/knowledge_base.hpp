#pragma once
#include"wumpus_world.hpp"
#include"types.hpp"
#include<functional>
#include<set>
#include<map>

namespace wumpus {

class KnowledgeBase {
public:
    KnowledgeBase();
    void tell(const WumpusWorld& world);
    void tell(const Action& action);
    Action ask(const WumpusWorld& world);

private:
    Direction turn_left(const Direction d)const;
    Direction turn_right(const Direction d)const;
    std::pair<int,int> believed_location = {1, 1};
    Direction believed_direction = Direction::EAST; // 0: North, 1: East, 2: South, 3: West
    std::set<std::pair<int,int>> visited;
    std::map<std::pair<int,int>, WumpusWorld::PerceptResult> known_percepts;
    std::set<std::pair<int,int>> known_safe;
    Action action_toward(std::pair<int,int>target)const;

};

}  // namespace wumpus
