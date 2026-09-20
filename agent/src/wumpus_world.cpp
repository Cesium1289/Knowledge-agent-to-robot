#include "agent/wumpus_world.hpp"

namespace wumpus {

const std::pair<int,int> WumpusWorld::EXIT_LOCATION = std::make_pair(1, 1);

WumpusWorld::WumpusWorld(std::pair<int, int> agent_Location, std::string agent_direction, bool agent_alive, bool wumpus_alive, std::pair<int, int> wumpus_location, std::pair<int, int> gold_location, std::vector<std::pair<int, int>> pit_locations)
{
    this->agent_location = agent_Location;
    this->agent_direction = agent_direction;
    this->agent_alive = agent_alive;
    this->wumpus_alive = wumpus_alive;
    this->wumpus_location = wumpus_location;
    this->gold_location = gold_location;
    this->pit_locations = pit_locations;
}

WumpusWorld::PerceptResult WumpusWorld::percept()
{
    PerceptResult percept;
    /*The current five-element percept in the `location`. Returns a tuple in the
        form of ('Stench', 'Breeze', 'Glitter', 'Bump', 'Scream'). Any of the elements
        within the returned percept tuple can be None.*/
     
    
        //check if agent is on wumpus or in the vicinity
        percept.stench = adjacent(agent_location,wumpus_location) || (agent_location == wumpus_location);
       
        //check if agent is ontop of the gold
        percept.glitter = gold_location == agent_location;
       
        //check if agent is against a wall
        percept.bump = agent_bumped_wall();

        //check if wumpus is dead
        percept.scream = !wumpus_alive;

        //check if near a pit
        percept.breeze = false;
        for(size_t i = 0; i < pit_locations.size();i++)
        {
            if(adjacent(agent_location,pit_locations.at(i)))
            {
                percept.breeze = true;
                break;
            }
        }
 
    return percept;
}
bool WumpusWorld::adjacent(std::pair<int,int> location, std::pair<int, int> target)
{  
  //  Is `location` immediately north, south, east or west of `target`?
    return (abs(location.first - target.first) + abs(location.second - target.second) == 1);
}
bool WumpusWorld::agent_bumped_wall()
{
    return false;
}
std::string WumpusWorld::get_agent_direction() const
{
    return agent_direction;
}
bool WumpusWorld::get_agent_is_alive() const
{
    return agent_alive;
}
} // namespace wumpus
