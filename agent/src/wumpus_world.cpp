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

    


// TODO: implement WumpusWorld
   char** percept(std::pair<int,int> location) {
         
        /*The current five-element percept in the `location`. Returns a tuple in the
        form of ('Stench', 'Breeze', 'Glitter', 'Bump', 'Scream'). Any of the elements
        within the returned percept tuple can be None.*/
     
        /*
        if (!location.first || !location.second)
        return "a";
        
        bool stench = "Stench" if self.adjacent(location,self.wumpus_location) or location == self.wumpus_location else None
        bool breeze = "Breeze" if any(self.adjacent(location, p) for p in self.pit_locations) else None
        bool glitter = "Glitter" if location == self.gold_location else None
        bool bump = "Bump" if self.agent_bumped_wall() else None
        bool scream = "Scream" if self.wumpus_alive == False else None
        return (stench,breeze,glitter,bump,scream)
        */
    }

   

} // namespace wumpus
