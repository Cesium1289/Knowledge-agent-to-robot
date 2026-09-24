#include "agent/knowledge_base.hpp"
#include <cmath>
#include <iostream>
using namespace std;
namespace wumpus {

// TODO: implement the inference engine

KnowledgeBase::KnowledgeBase()
{
}

void KnowledgeBase::tell(const WumpusWorld &world) 
{
    auto percept = world.percept();

    visited.insert(believed_location);
    known_percepts[believed_location] = percept;
    //adjacent squares must be safe
    if(percept.breeze == false && percept.stench == false)
    {
        //check if we can move east
        if(believed_location.first < 4)
            known_safe.insert(std::make_pair(believed_location.first+1, believed_location.second));
        if(believed_location.first > 1)
        known_safe.insert(std::make_pair(believed_location.first -1, believed_location.second));
        if(believed_location.second < 4)
            known_safe.insert(std::make_pair(believed_location.first, believed_location.second+1));
        if(believed_location.second > 1)
            known_safe.insert(std::make_pair(believed_location.first, believed_location.second-1));
    }
}

void KnowledgeBase::tell(const Action& action) 
{
     if (action == Action::TURN_LEFT)
    {
        if (believed_direction == "North") 
            believed_direction = "West";
        else if (believed_direction == "West") 
            believed_direction = "South";
        else if (believed_direction == "South") 
            believed_direction = "East";
        else if (believed_direction == "East") 
                believed_direction = "North";
    }
    else if (action == Action::TURN_RIGHT)
    {
        if (believed_direction == "North") 
            believed_direction = "East";
        else if (believed_direction == "East") 
            believed_direction = "South";
        else if (believed_direction == "South") 
            believed_direction = "West";
        else if (believed_direction == "West") 
            believed_direction = "North";
    }
    else if (action == Action::MOVE_FORWARD)
    {
        if (believed_direction == "North" && believed_location.second < 4)
            believed_location.second++;
        else if (believed_direction == "South" && believed_location.second > 1)
            believed_location.second--;
        else if (believed_direction == "East" && believed_location.first < 4)
            believed_location.first++;
        else if (believed_direction == "West" && believed_location.first > 1)
            believed_location.first--;
    }

}

Action KnowledgeBase::ask(const WumpusWorld &world) 
{
     if ((believed_location == WumpusWorld::EXIT_LOCATION) && world.get_agent_has_gold())
     {
         cout<<"i lewave the gold\n";
         return Action::CLIMB;

     }
    if (world.percept().glitter == true)
    {
        std::cout<<"i foudn the gold\n";
        return Action::GRAB;
    }

    // find the closest known-safe, unvisited square (not necessarily adjacent)
    bool found = false;
    std::pair<int,int> target;
    int best_distance = 0;

    for (auto square : known_safe)
    {
        if (visited.find(square) != visited.end())
            continue;  // already been there

        int distance = std::abs(square.first - believed_location.first)
                      + std::abs(square.second - believed_location.second);

        if (!found || distance < best_distance)
        {
            found = true;
            target = square;
            best_distance = distance;
        }
    }

    if (found)
        return action_toward(target);

    // nothing left to explore — head back to the exit
    if (believed_location == WumpusWorld::EXIT_LOCATION)
    {
        cout <<"here\n";
        return Action::CLIMB;
    }

    return action_toward(WumpusWorld::EXIT_LOCATION);
}

Action KnowledgeBase::action_toward(std::pair<int, int> target) const
{
    if (target.first > believed_location.first)
    {
        if (believed_direction == "North") return Action::TURN_RIGHT;
        else if (believed_direction == "South") return Action::TURN_LEFT;
        else if (believed_direction == "West") return Action::TURN_LEFT;
        else if (believed_direction == "East") return Action::MOVE_FORWARD;
    }
    else if (target.first < believed_location.first)
    {
        if (believed_direction == "North") return Action::TURN_LEFT;
        else if (believed_direction == "South") return Action::TURN_RIGHT;
        else if (believed_direction == "West") return Action::MOVE_FORWARD;
        else if (believed_direction == "East") return Action::TURN_RIGHT;
    }
    else if (target.second > believed_location.second)
    {
        if (believed_direction == "North") return Action::MOVE_FORWARD;
        else if (believed_direction == "South") return Action::TURN_RIGHT;
        else if (believed_direction == "West") return Action::TURN_RIGHT;
        else if (believed_direction == "East") return Action::TURN_LEFT;
    }
    else if (target.second < believed_location.second)
    {
        if (believed_direction == "North") return Action::TURN_RIGHT;
        else if (believed_direction == "South") return Action::MOVE_FORWARD;
        else if (believed_direction == "West") return Action::TURN_LEFT;
        else if (believed_direction == "East") return Action::TURN_RIGHT;
    }

    // target == believed_location — already there, nothing meaningful to return
    return Action::CLIMB;
}

} // namespace wumpus
