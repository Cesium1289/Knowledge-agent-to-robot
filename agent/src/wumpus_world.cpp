#include "agent/wumpus_world.hpp"

namespace wumpus {

const std::pair<int,int> WumpusWorld::EXIT_LOCATION = std::make_pair(1, 1);

WumpusWorld::WumpusWorld(std::pair<int, int> agent_Location, Direction agent_direction, bool agent_alive, bool wumpus_alive, std::pair<int, int> wumpus_location, std::pair<int, int> gold_location, std::vector<std::pair<int, int>> pit_locations)
{
    this->agent_location = agent_Location;
    this->agent_direction = agent_direction;
    this->agent_alive = agent_alive;
    this->wumpus_alive = wumpus_alive;
    this->wumpus_location = wumpus_location;
    this->gold_location = gold_location;
    this->pit_locations = pit_locations;
}

WumpusWorld::PerceptResult WumpusWorld::percept()const
{
    PerceptResult percept;
    /*The current five-element percept in the `location`. Returns a tuple in the
        form of ('Stench', 'Breeze', 'Glitter', 'Bump', 'Scream'). Any of the elements
        within the returned percept tuple can be None.*/
    
        //check if agent is on wumpus or in the vicinity
        percept.stench = adjacent(agent_location,wumpus_location) || (agent_location == wumpus_location);
       
        //check if agent is ontop of the gold
        percept.glitter = (gold_location == agent_location) && !has_gold;
       
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
void WumpusWorld::turned_left()
{
    switch(agent_direction)
    {
        case NORTH: agent_direction = WEST;
            break;  
        case WEST: agent_direction = SOUTH;
            break;
        case SOUTH: agent_direction = EAST;
            break;
        case EAST: agent_direction = NORTH;
    }
}
void WumpusWorld::turned_right()
{
     switch(agent_direction)
    {
        case NORTH: agent_direction = EAST;
            break;  
        case WEST: agent_direction = NORTH;
            break;
        case SOUTH: agent_direction = WEST;
            break;
        case EAST: agent_direction = SOUTH;
    }
}

void WumpusWorld::move_forward()
{
    // check if and where the agent should move
    if (agent_direction == Direction::NORTH && agent_can_move_north())
        agent_location.second++;
    else if (agent_direction ==  Direction::SOUTH && agent_can_move_south())
        agent_location.second--;
    else if (agent_direction ==  Direction::EAST && agent_can_move_east())
        agent_location.first++;
    else if (agent_direction ==  Direction::WEST && agent_can_move_west())
        agent_location.first--;

    // check if agent is in a pit
    for (const auto& pit : pit_locations) {
        if (agent_location == pit) {
            agent_alive = false;
            break;
        }
    }

    // check if agent is with a living wumpus
    if (agent_location == wumpus_location && wumpus_alive) 
        agent_alive = false;
    
    
}

void WumpusWorld::grabbed()
{
    if(!has_gold && (agent_location == gold_location))
        has_gold = true;
}

void WumpusWorld::climbed()
{
    if(agent_location == EXIT_LOCATION)
        has_climbed_out = true;
}

void WumpusWorld::shot()
{
    //Shoot the arrow. If the arrow strikes the wumpus, then the wumpus should
    //no longer be alive.
        
        //check agent direction and if the wumpus is in the same direction
        if (agent_direction == Direction::NORTH && wumpus_north_of_agent())
            wumpus_alive = false;
        else if(agent_direction == Direction::SOUTH && wumpus_south_of_agent())
            wumpus_alive = false;
        else if(agent_direction ==  Direction::WEST && wumpus_west_of_agent())
            wumpus_alive = false;
        else if (agent_direction ==  Direction::EAST && wumpus_east_of_agent())
            wumpus_alive = false;
}

 bool WumpusWorld::adjacent(std::pair<int, int> location, std::pair<int, int> target)
{  
  //  Is `location` immediately north, south, east or west of `target`?
    return (abs(location.first - target.first) + abs(location.second - target.second) == 1);
}
bool WumpusWorld::agent_can_move_east()const
{
    return agent_location.first < 4;
}
bool WumpusWorld::agent_can_move_west()const
{
    return agent_location.first > 1;
}
bool WumpusWorld::agent_can_move_north()const
{
    return agent_location.second < 4;
}
bool WumpusWorld::agent_can_move_south()const
{
   return agent_location.second > 1;
}
bool WumpusWorld::agent_bumped_wall()const
{ 
    //Did the agent bump into a wall? (Or, is the agent facing a wall?)

        //check west
        if(!agent_can_move_west() && agent_direction ==  Direction::WEST)
            return true;
        
        //check east
        if(!agent_can_move_east() && agent_direction ==  Direction::EAST)
            return true;
        
        //check north
        if(!agent_can_move_north() && agent_direction ==  Direction::NORTH)
            return true;
        
        //check south
        if(!agent_can_move_south() && agent_direction ==  Direction::SOUTH)
            return true;
        
        return false;
}
bool WumpusWorld::wumpus_east_of_agent()const
{
    // Is the wumpus somewhere to the east of the agent?
    return agent_location.first < wumpus_location.first && agent_location.second == wumpus_location.second;
}
bool WumpusWorld::wumpus_west_of_agent()const
{
    //Is the wumpus somewhere to the west of the agent?
    return agent_location.first > wumpus_location.first && agent_location.second == wumpus_location.second;
}
bool WumpusWorld::wumpus_north_of_agent()const
{
    //Is the wumpus somewhere to the north of the agent?
    return agent_location.first == wumpus_location.first && agent_location.second < wumpus_location.second;
}
bool WumpusWorld::wumpus_south_of_agent()const
{
    //Is the wumpus somewhere to the south of the agent?
    return agent_location.first == wumpus_location.first && agent_location.second > wumpus_location.second;
}
Direction WumpusWorld::get_agent_direction() const
{
    return agent_direction;
}
bool WumpusWorld::get_agent_is_alive() const
{
    return agent_alive;
}
bool WumpusWorld::get_agent_has_gold() const
{
    return has_gold;
}
bool WumpusWorld::get_has_climbed_out() const
{
    return has_climbed_out;
}
} // namespace wumpus
