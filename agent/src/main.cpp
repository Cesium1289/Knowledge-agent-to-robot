#include <iostream>
#include "utility"
#include "agent/wumpus_world.hpp"
#include "agent/knowledge_base.hpp"
#include "agent/wumpus_world_agent.hpp"
// Demonstration entry point for the Wumpus World agent.
// TODO: instantiate WumpusWorld, KnowledgeBase, and WumpusWorldAgent here,
// then run the agent loop, once those classes are implemented.

std::string action_to_string(wumpus::Action action)
{
    switch (action)
    {
        case wumpus::Action::TURN_LEFT:    return "turn left";
        case wumpus::Action::TURN_RIGHT:   return "turn right";
        case wumpus::Action::MOVE_FORWARD: return "move forward";
        case wumpus::Action::SHOOT:        return "shoot";
        case wumpus::Action::GRAB:         return "grab";
        case wumpus::Action::CLIMB:        return "climb";
    }
    return "unknown";
}

int main()
{
    wumpus::WumpusWorld world(
        std::make_pair(1, 1),
        "East", true, true,
        std::make_pair(3, 3),
        std::make_pair(2, 2),
        {std::make_pair(4, 2), std::make_pair(2, 3), std::make_pair(4, 4)}
    );

    wumpus::KnowledgeBase kb;
    wumpus::WumpusWorldAgent agent(kb);

    const int max_steps = 100;
    int step = 0;

    while (world.get_agent_is_alive() && !world.get_has_climbed_out() && step < max_steps)
    {
        wumpus::Action decision = agent.action(world);
        std::cout << "Step " << step << ": " << action_to_string(decision)
                  << " | direction=" << world.get_agent_direction()
                  << " | alive=" << world.get_agent_is_alive()
                  << " | has_gold=" << world.get_agent_has_gold()
                  << " | climbed_out=" << world.get_has_climbed_out()
                  << "\n";
        step++;
    }

    if (!world.get_agent_is_alive())
        std::cout << "\nThe agent died.\n";
    else if (world.get_has_climbed_out())
        std::cout << "\nThe agent climbed out"
                  << (world.get_agent_has_gold() ? " with the gold. Success!\n" : " without the gold.\n");
    else
        std::cout << "\nStopped after " << max_steps << " steps without finishing.\n";

    return 0;
}
