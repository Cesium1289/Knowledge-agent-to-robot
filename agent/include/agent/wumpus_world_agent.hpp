#pragma once
#include"wumpus_world.hpp"
#include"knowledge_base.hpp"
namespace wumpus {

class WumpusWorldAgent {
public:
    WumpusWorldAgent(KnowledgeBase& knowledge_base);
    void turn_left(WumpusWorld& world)const;
    void turn_right(WumpusWorld& world)const; 
    void move_forward(WumpusWorld& world)const;
    void shoot(WumpusWorld& world)const;
    void grab(WumpusWorld& world)const;
    void climb(WumpusWorld& world)const;
    

    //TO DO
    void make_percept_Sentence( WumpusWorld& world)const;
    void make_action_query();
    void make_action_sentence();
    Action action(WumpusWorld& world);

private:
    KnowledgeBase& kb;
    int num_actions = 0;
};

}//wumpus