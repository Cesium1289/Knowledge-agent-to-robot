#pragma once
#include"wumpus_world.hpp"
// WumpusWorldAgent
// A knowledge-based agent following the AIMA KB-AGENT specification:
// tell the KB what's perceived, ask the KB what to do, tell the KB the
// action taken, return the action.
//
// TODO: port actuator methods and the action() loop from the Python
// reference implementation.

namespace wumpus {

class WumpusWorldAgent {
public:
    WumpusWorldAgent();
    void turn_left()const;
    void turn_right()const; 
    void move_forward()const;
    void shoot()const;
    void grab()const;
    void climb();
    

    //TO DO
    void make_percept_Sentence(WumpusWorld world);
    void make_action_query();
    void make_action_sentence();
    void action(WumpusWorld world);

    };

}//wumpus