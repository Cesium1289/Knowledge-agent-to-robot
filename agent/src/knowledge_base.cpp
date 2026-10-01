#include "agent/knowledge_base.hpp"
#include <cmath>
#include <iostream>
using namespace std;
namespace wumpus {

KnowledgeBase::KnowledgeBase()
{
}

void KnowledgeBase::tell(const WumpusWorld &world) 
{
    auto percept = world.percept();

    visited.insert(believed_location);
    known_percepts[believed_location] = percept;

    //adjacent squares must be safe since nothing was perceived
    if(percept.breeze == false && percept.stench == false)
    {
        //loop through the four adjacent squares
        for(int i = 0; i < 4; i++)
        {
            int nx = believed_location.first + DX[i];
            int ny = believed_location.second + DY[i];

            //check if the adjacent square is within the bounds of the world
            if (nx >= 1 && nx <= 4 && ny >= 1 && ny <= 4)
                known_safe.insert(std::make_pair(nx, ny));
        }
    }
}

void KnowledgeBase::tell(const Action& action) 
{
     if (action == Action::TURN_LEFT)
        believed_direction = turn_left(believed_direction);
    else if (action == Action::TURN_RIGHT)
        believed_direction = turn_right(believed_direction);
    else if (action == Action::MOVE_FORWARD)
    {
        int nx = believed_location.first + DX[believed_direction];
        int ny = believed_location.second + DY[believed_direction];
        if (nx >= 1 && nx <= 4 && ny >= 1 && ny <= 4)
            believed_location = std::make_pair(nx, ny);
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

wumpus::Direction KnowledgeBase::turn_left(const Direction d)const
{
    switch(d)
    {
        case NORTH: return WEST;
        case WEST: return SOUTH;
        case SOUTH: return EAST;
        case EAST: return NORTH;
    }
    return d;
}

wumpus::Direction KnowledgeBase::turn_right(const Direction d)const
{
    switch(d)
    {
        case NORTH: return EAST;
        case EAST: return SOUTH;
        case SOUTH: return WEST;
        case WEST: return NORTH;
    }
    return d;
}

Action KnowledgeBase::action_toward(std::pair<int, int> target) const
{
    //check if target is east
    if (target.first > believed_location.first)
    {
        if (believed_direction == 0) return Action::TURN_RIGHT;
        else if (believed_direction == 2) return Action::TURN_LEFT;
        else if (believed_direction == 3) return Action::TURN_LEFT;
        else if (believed_direction == 1) return Action::MOVE_FORWARD;
    }
    //check if the target is west
    else if (target.first < believed_location.first)
    {
        if (believed_direction == 0) return Action::TURN_LEFT;
        else if (believed_direction == 2) return Action::TURN_RIGHT;
        else if (believed_direction == 3) return Action::MOVE_FORWARD;
        else if (believed_direction == 1) return Action::TURN_RIGHT;
    }
    //check if the target is north
    else if (target.second > believed_location.second)
    {
        if (believed_direction == 0) return Action::MOVE_FORWARD;
        else if (believed_direction == 2) return Action::TURN_RIGHT;
        else if (believed_direction == 3) return Action::TURN_RIGHT;
        else if (believed_direction == 1) return Action::TURN_LEFT;
    }
    //check if the target is south
    else if (target.second < believed_location.second)
    {
        if (believed_direction == 0) return Action::TURN_RIGHT;
        else if (believed_direction == 2) return Action::MOVE_FORWARD;
        else if (believed_direction == 3) return Action::TURN_LEFT;
        else if (believed_direction == 1) return Action::TURN_RIGHT;
    }

    // target == believed_location — already there, nothing meaningful to return
    return Action::CLIMB;
}

} // namespace wumpus
