#include <iostream>
#include "utility"
#include "agent/wumpus_world.hpp"
// Demonstration entry point for the Wumpus World agent.
// TODO: instantiate WumpusWorld, KnowledgeBase, and WumpusWorldAgent here,
// then run the agent loop, once those classes are implemented.

int main() {
    std::cout << "Wumpus World agent scaffold — nothing implemented yet.\n";
    wumpus::WumpusWorld world(
        std::make_pair(1, 1),   // agent_location
        "East",
        true,
        true,
        std::make_pair(1, 2),   // wumpus_location — adjacent to agent
        std::make_pair(4, 4),   // gold_location — far away
        {std::make_pair(4, 2), std::make_pair(2,1)}  // pit_locations — far away
    );

    wumpus::WumpusWorld::PerceptResult percept = world.percept();

    return 0;
    
}
