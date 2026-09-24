#include "agent/wumpus_world_agent.hpp"

namespace wumpus {

// TODO: implement WumpusWorldAgent

WumpusWorldAgent::WumpusWorldAgent(KnowledgeBase &knowledge_base)
:kb(knowledge_base)
{
    num_actions = 0;
}

void WumpusWorldAgent::turn_left(WumpusWorld &world) const
{
    world.turned_left();
}

void WumpusWorldAgent::turn_right(WumpusWorld &world) const
{
    world.turned_right();
}

void WumpusWorldAgent::move_forward(WumpusWorld &world) const
{
    world.move_forward();
}

void WumpusWorldAgent::shoot(WumpusWorld &world) const
{
    world.shot();
}

void WumpusWorldAgent::grab(WumpusWorld &world) const
{
    world.grabbed();
}

void WumpusWorldAgent::climb(WumpusWorld &world) const
{
    world.climbed();
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

    if (decision == Action::TURN_LEFT)
        turn_left(world);
    else if (decision == Action::TURN_RIGHT)   
        turn_right(world);
    else if (decision == Action::MOVE_FORWARD) 
        move_forward(world);
    else if (decision == Action::SHOOT)       
        shoot(world);
    else if (decision == Action::GRAB)        
        grab(world);
    else if (decision == Action::CLIMB)      
        climb(world);

    kb.tell(decision);
    num_actions++;
    return decision;

}

} // namespace wumpus
