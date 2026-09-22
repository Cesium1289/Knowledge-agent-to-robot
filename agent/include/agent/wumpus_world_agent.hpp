#pragma once
#include"wumpus_world.hpp"
#include"knowledge_base.hpp"
namespace wumpus {

class WumpusWorldAgent {
public:
    WumpusWorldAgent(KnowledgeBase& kb);
    void turn_left(WumpusWorld& world)const;
    void turn_right(WumpusWorld& world)const; 
    void move_forward(WumpusWorld& world)const;
    void shoot(WumpusWorld& world)const;
    void grab(WumpusWorld& world)const;
    void climb(WumpusWorld& world)const;
    

    //TO DO
    void make_percept_Sentence(WumpusWorld& world);
    void make_action_query();
    void make_action_sentence();
    void action(WumpusWorld& world);

private:
    KnowledgeBase& kb;
    int time = 0;
};

}//wumpus