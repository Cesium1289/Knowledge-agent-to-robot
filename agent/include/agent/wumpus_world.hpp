#pragma once
#include <utility> 
#include <vector>
#include <string>
#include <cstdlib>
// WumpusWorld
// Simulated physical environment: the "real" 4x4 cave, its physics, and the
// percepts it emits. This is NOT the agent's belief state — it is reality.
//
// TODO: port from the Python reference implementation, then extend/adjust
// as needed once the C++ agent's needs are clearer.

namespace wumpus {

class WumpusWorld {
public:

static const std::pair<int,int> EXIT_LOCATION;

 struct PerceptResult{
    bool stench = false;
    bool breeze = false;
    bool glitter = false;
    bool bump = false;
    bool scream = false;
    };
    // TODO: constructor, percept(), and physical action side effects
    // (turned_left, turned_right, moved_forward, grabbed, climbed, shot).
    WumpusWorld(
        std::pair<int,int> agent_location = std::make_pair(1,1),
        std::string agent_direction = "East",
        bool agent_alive = true,
        bool wumpus_alive = true,
        std::pair<int,int> wumpus_location =std::make_pair(3,3), 
        std::pair<int,int> gold_location = std::make_pair(2,2), 
        std::vector<std::pair<int,int>> pit_locations={std::make_pair(1,2), std::make_pair(2,3), std::make_pair(4,4)});
    
    PerceptResult percept()const;

    void turned_left();
    void turned_right();
    void move_forward();
    void grabbed();
    void climbed();
    void shot();
    std::string get_agent_direction()const;
    bool get_agent_is_alive()const;
    bool get_agent_has_gold()const;

    
private:    
    std::pair<int,int> agent_location;
    std::string agent_direction;
    bool agent_alive;
    bool wumpus_alive;
    std::pair<int,int> wumpus_location;
    std::pair<int,int> gold_location;
    std::vector<std::pair<int,int>> pit_locations;
    bool has_gold = false;

    bool adjacent(std::pair<int,int> current, std::pair<int,int> target)const;
    bool agent_can_move_east()const;
    bool agent_can_move_west()const;
    bool agent_can_move_north()const;
    bool agent_can_move_south()const;
    bool agent_bumped_wall()const;
    bool wumpus_east_of_agent()const;
    bool wumpus_west_of_agent()const;
    bool wumpus_north_of_agent()const;
    bool wumpus_south_of_agent()const;


};

}  // namespace wumpus
