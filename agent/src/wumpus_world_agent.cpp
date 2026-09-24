#include "agent/wumpus_world_agent.hpp"

namespace wumpus {

// TODO: implement WumpusWorldAgent

WumpusWorldAgent::WumpusWorldAgent(KnowledgeBase &knowledge_base)
{
    kb = knowledge_base;
    num_actions = 0;
}

void WumpusWorldAgent::turn_left(WumpusWorld &world) const
{
}

void WumpusWorldAgent::turn_right(WumpusWorld &world) const
{
}

void WumpusWorldAgent::move_forward(WumpusWorld &world) const
{
}

void WumpusWorldAgent::shoot(WumpusWorld &world) const
{
}

void WumpusWorldAgent::grab(WumpusWorld &world) const
{
}

void WumpusWorldAgent::climb(WumpusWorld &world) const
{
}

void WumpusWorldAgent::make_percept_Sentence(WumpusWorld &world)const
{
}

void WumpusWorldAgent::make_action_query()
{
}

void WumpusWorldAgent::make_action_sentence()
{
}

Action WumpusWorldAgent::action( WumpusWorld &world)
{
    // Agent tells kb what it sees, asks for an action based on
    //what it sees, then returns the action it recieved
    kb.tell(world);
    Action decision = kb.ask(world);
    kb.tell(decision);
    num_actions++;
    return decision;

}

} // namespace wumpus
