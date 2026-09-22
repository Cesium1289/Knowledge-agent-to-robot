#include <catch2/catch_test_macros.hpp>
#include "agent/wumpus_world.hpp"

/*
* initialization Tests
*/
TEST_CASE("Default constructor success", "[WumpusWorld]") {
    REQUIRE_NOTHROW(wumpus::WumpusWorld());
}
TEST_CASE("Arg constructor success", "[WumpusWorld]") {
    REQUIRE_NOTHROW(wumpus::WumpusWorld( std::make_pair(1, 1),
    "East", true, true,
    std::make_pair(1, 2),
    std::make_pair(4, 4),
   {std::make_pair(3, 3)}));
}

TEST_CASE("Initialize wumpusworld", "[WumpusWorld]") {
    wumpus::WumpusWorld world(
        std::make_pair(1, 1),
        "East", true, true,
        std::make_pair(1, 2),   // wumpus adjacent to agent
        std::make_pair(4, 4),
        {std::make_pair(3, 3)}
    );

    auto result = world.percept();
    REQUIRE(result.stench == true);
    REQUIRE(result.breeze == false);
    REQUIRE(result.glitter == false);
}

/* 
* Property tests
*/
TEST_CASE("agent direction success", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld( std::make_pair(1, 1),
    "East", true, true,
    std::make_pair(1, 2),
    std::make_pair(4, 4),
   {std::make_pair(3, 3)});
   REQUIRE(world.get_agent_direction() == "East");
}

TEST_CASE("agent is alive success", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld( std::make_pair(1, 1),
    "East", true, true,
    std::make_pair(1, 2),
    std::make_pair(4, 4),
   {std::make_pair(3, 3)});
   REQUIRE(world.get_agent_is_alive() == true);
}

TEST_CASE("wumpus is alive success", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld( std::make_pair(1, 1),
    "East", true, true,
    std::make_pair(1, 2),
    std::make_pair(4, 4),
   {std::make_pair(3, 3)});
   auto result = world.percept();
   REQUIRE(result.scream == false);
}

TEST_CASE("Percept scream when wumpus is dead", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld(std::make_pair(1, 1),
        "East", true, false,  
        std::make_pair(4, 4),
        std::make_pair(2, 2),
        {std::make_pair(3, 3)});
    auto result = world.percept();
    REQUIRE(result.scream == true);
}

/*
* Percept Tests
*/

TEST_CASE("Percept no stench", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld(std::make_pair(2, 2),
        "East", true, true,
        std::make_pair(4, 4),   // wumpus far away
        std::make_pair(1, 1),
        {std::make_pair(3, 3)});
    auto result = world.percept();
    REQUIRE(result.stench == false);
}
TEST_CASE("Percept stench north", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld( std::make_pair(2, 2),
    "East", true, true,
    std::make_pair(2, 3), //wumpus location
    std::make_pair(4, 4),
   {std::make_pair(3, 3)});
   auto result = world.percept();
   REQUIRE(result.stench == true);
}

TEST_CASE("Percept stench south", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld( std::make_pair(2, 2),
    "East", true, true,
    std::make_pair(2, 1), //wumpus location
    std::make_pair(4, 4),
   {std::make_pair(3, 3)});
   auto result = world.percept();
   REQUIRE(result.stench == true);
}

TEST_CASE("Percept stench east", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld( std::make_pair(2, 2),
    "East", true, true,
    std::make_pair(3, 2), //wumpus location
    std::make_pair(4, 4),
   {std::make_pair(3, 3)});
   auto result = world.percept();
   REQUIRE(result.stench == true);
}

TEST_CASE("Percept stench west", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld( std::make_pair(2, 2),
    "East", true, true,
    std::make_pair(1, 2), //wumpus location
    std::make_pair(4, 4),
   {std::make_pair(3, 3)});
   auto result = world.percept();
   REQUIRE(result.stench == true);
}


TEST_CASE("Percept breeze north", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld( std::make_pair(2, 2),
    "East", true, true,
    std::make_pair(1, 3), 
    std::make_pair(4, 4),
   {std::make_pair(2, 3)}); //pit location
   auto result = world.percept();
   REQUIRE(result.breeze == true);
}

TEST_CASE("Percept breeze south", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld( std::make_pair(2, 2),
    "East", true, true,
    std::make_pair(1, 3), 
    std::make_pair(4, 4),
   {std::make_pair(2, 1)}); //pit location
   auto result = world.percept();
   REQUIRE(result.breeze == true);
}

TEST_CASE("Percept breeze east", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld( std::make_pair(2, 2),
    "East", true, true,
    std::make_pair(1, 3), 
    std::make_pair(4, 4),
   {std::make_pair(3, 2)}); //pit location
   auto result = world.percept();
   REQUIRE(result.breeze == true);
}

TEST_CASE("Percept breeze west", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld( std::make_pair(2, 2),
    "East", true, true,
    std::make_pair(1, 3), //wumpus location
    std::make_pair(4, 4),
   {std::make_pair(1, 2)});// pit location
   auto result = world.percept();
   REQUIRE(result.breeze == true);
}

TEST_CASE("Percept no breeze", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld( std::make_pair(2, 2),
    "East", true, true,
    std::make_pair(1, 3), 
    std::make_pair(4, 4),
   {std::make_pair(3, 3)});// pit location
   auto result = world.percept();
   REQUIRE(result.breeze == false);
}

TEST_CASE("Percept breeze from multiple adjacent pits", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld(std::make_pair(2, 2),
        "East", true, true,
        std::make_pair(4, 4),
        std::make_pair(1, 1),
        {std::make_pair(2, 3), std::make_pair(2, 1)});  // two pits, both adjacent
    auto result = world.percept();
    REQUIRE(result.breeze == true);
}

TEST_CASE("Percept glitter", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld( std::make_pair(2, 2),
    "East", true, true,
    std::make_pair(1, 3), 
    std::make_pair(2, 2),
   {std::make_pair(1, 2)});
   auto result = world.percept();
   REQUIRE(result.glitter == true);
}

TEST_CASE("Percept no glitter", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld( std::make_pair(2, 2),
    "East", true, true,
    std::make_pair(1, 3), 
    std::make_pair(3, 2),
   {std::make_pair(1, 2)});
   auto result = world.percept();
   REQUIRE(result.glitter == false);
}

/*
* agent bumped wall tests
*/
TEST_CASE("agenet facing North in center and not bump into wall", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld( std::make_pair(2, 2),
    "North", true, true,
    std::make_pair(1, 3), 
    std::make_pair(3, 2),
   {std::make_pair(1, 2)});
    auto percept = world.percept();
    REQUIRE(percept.bump == false);
}

TEST_CASE("agenet facing East in center and not bump into wall", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld( std::make_pair(2, 2),
    "East", true, true,
    std::make_pair(1, 3), 
    std::make_pair(3, 2),
   {std::make_pair(1, 2)});
    auto percept = world.percept();
    REQUIRE(percept.bump == false);
}

TEST_CASE("agenet facing South in center and not bump into wall", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld( std::make_pair(2, 2),
    "South", true, true,
    std::make_pair(1, 3), 
    std::make_pair(3, 2),
   {std::make_pair(1, 2)});
    auto percept = world.percept();
    REQUIRE(percept.bump == false);
}

TEST_CASE("agenet facing West in center and not bump into wall", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld( std::make_pair(2, 2),
    "West", true, true,
    std::make_pair(1, 3), 
    std::make_pair(3, 2),
   {std::make_pair(1, 2)});
    auto percept = world.percept();
    REQUIRE(percept.bump == false);
}

TEST_CASE("Agent bumps wall at (1,4) facing West or North", "[WumpusWorld]") {
    auto world_west = wumpus::WumpusWorld(std::make_pair(1, 4),
        "West", true, true,
        std::make_pair(1, 3),
        std::make_pair(3, 2),
        {std::make_pair(1, 2)});
    REQUIRE(world_west.percept().bump == true);

    auto world_north = wumpus::WumpusWorld(std::make_pair(1, 4),
        "North", true, true,
        std::make_pair(1, 3),
        std::make_pair(3, 2),
        {std::make_pair(1, 2)});
    REQUIRE(world_north.percept().bump == true);
}

TEST_CASE("Agent bumps wall at (4,1) facing East or South", "[WumpusWorld]") {
    auto world_east = wumpus::WumpusWorld(std::make_pair(4, 1),
        "East", true, true,
        std::make_pair(1, 3),
        std::make_pair(3, 2),
        {std::make_pair(1, 2)});
    REQUIRE(world_east.percept().bump == true);

    auto world_south = wumpus::WumpusWorld(std::make_pair(4, 1),
        "South", true, true,
        std::make_pair(1, 3),
        std::make_pair(3, 2),
        {std::make_pair(1, 2)});
    REQUIRE(world_south.percept().bump == true);
}

TEST_CASE("Agent bumps wall at (4,4) facing East or North", "[WumpusWorld]") {
    auto world_east = wumpus::WumpusWorld(std::make_pair(4, 4),
        "East", true, true,
        std::make_pair(1, 3),
        std::make_pair(3, 2),
        {std::make_pair(1, 2)});
    REQUIRE(world_east.percept().bump == true);

    auto world_north = wumpus::WumpusWorld(std::make_pair(4, 4),
        "North", true, true,
        std::make_pair(1, 3),
        std::make_pair(3, 2),
        {std::make_pair(1, 2)});
    REQUIRE(world_north.percept().bump == true);
}

TEST_CASE("Agent bumps wall at (1,1) facing West or South", "[WumpusWorld]") {
    auto world_west = wumpus::WumpusWorld(std::make_pair(1, 1),
        "West", true, true,
        std::make_pair(1, 3),
        std::make_pair(3, 2),
        {std::make_pair(1, 2)});
    REQUIRE(world_west.percept().bump == true);

    auto world_south = wumpus::WumpusWorld(std::make_pair(1, 1),
        "South", true, true,
        std::make_pair(1, 3),
        std::make_pair(3, 2),
        {std::make_pair(1, 2)});
    REQUIRE(world_south.percept().bump == true);
}

/*
 * turned_left / turned_right tests
*/
TEST_CASE("Turning left from North faces West", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld(std::make_pair(2, 2),
        "North", true, true,
        std::make_pair(1, 3),
        std::make_pair(3, 2),
        {std::make_pair(1, 2)});
    world.turned_left();
    REQUIRE(world.get_agent_direction() == "West");
}

TEST_CASE("Turning left from West faces South", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld(std::make_pair(2, 2),
        "West", true, true,
        std::make_pair(1, 3),
        std::make_pair(3, 2),
        {std::make_pair(1, 2)});
    world.turned_left();
    REQUIRE(world.get_agent_direction() == "South");
}

TEST_CASE("Turning left from South faces East", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld(std::make_pair(2, 2),
        "South", true, true,
        std::make_pair(1, 3),
        std::make_pair(3, 2),
        {std::make_pair(1, 2)});
    world.turned_left();
    REQUIRE(world.get_agent_direction() == "East");
}

TEST_CASE("Turning left from East faces North", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld(std::make_pair(2, 2),
        "East", true, true,
        std::make_pair(1, 3),
        std::make_pair(3, 2),
        {std::make_pair(1, 2)});
    world.turned_left();
    REQUIRE(world.get_agent_direction() == "North");
}

TEST_CASE("Turning right from North faces East", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld(std::make_pair(2, 2),
        "North", true, true,
        std::make_pair(1, 3),
        std::make_pair(3, 2),
        {std::make_pair(1, 2)});
    world.turned_right();
    REQUIRE(world.get_agent_direction() == "East");
}

TEST_CASE("Turning right from East faces South", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld(std::make_pair(2, 2),
        "East", true, true,
        std::make_pair(1, 3),
        std::make_pair(3, 2),
        {std::make_pair(1, 2)});
    world.turned_right();
    REQUIRE(world.get_agent_direction() == "South");
}

TEST_CASE("Turning right from South faces West", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld(std::make_pair(2, 2),
        "South", true, true,
        std::make_pair(1, 3),
        std::make_pair(3, 2),
        {std::make_pair(1, 2)});
    world.turned_right();
    REQUIRE(world.get_agent_direction() == "West");
}

TEST_CASE("Turning right from West faces North", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld(std::make_pair(2, 2),
        "West", true, true,
        std::make_pair(1, 3),
        std::make_pair(3, 2),
        {std::make_pair(1, 2)});
    world.turned_right();
    REQUIRE(world.get_agent_direction() == "North");
}

/*
* move_forward tests
*/
TEST_CASE("Move forward East succeeds", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld(std::make_pair(2, 2),
        "East", true, true,
        std::make_pair(1, 4),
        std::make_pair(3, 2),   // gold at destination
        {std::make_pair(1, 1)});
    world.move_forward();
    REQUIRE(world.percept().glitter == true);
}

TEST_CASE("Move forward West succeeds", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld(std::make_pair(3, 2),
        "West", true, true,
        std::make_pair(1, 4),
        std::make_pair(2, 2),   // gold at destination
        {std::make_pair(1, 1)});
    world.move_forward();
    REQUIRE(world.percept().glitter == true);
}

TEST_CASE("Move forward North succeeds", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld(std::make_pair(2, 2),
        "North", true, true,
        std::make_pair(1, 4),
        std::make_pair(2, 3),   // gold at destination
        {std::make_pair(1, 1)});
    world.move_forward();
    REQUIRE(world.percept().glitter == true);
}

TEST_CASE("Move forward South succeeds", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld(std::make_pair(2, 3),
        "South", true, true,
        std::make_pair(1, 4),
        std::make_pair(2, 2),   // gold at destination
        {std::make_pair(1, 1)});
    world.move_forward();
    REQUIRE(world.percept().glitter == true);
}

TEST_CASE("Move forward blocked by wall does not move agent", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld(std::make_pair(4, 2),
        "East", true, true,
        std::make_pair(1, 4),
        std::make_pair(4, 2),   // gold at agent's own square
        {std::make_pair(1, 1)});
    world.move_forward();
    // agent never left, so it's still standing on the gold
    REQUIRE(world.percept().glitter == true);
}

TEST_CASE("Moving into a pit kills the agent", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld(std::make_pair(2, 2),
        "East", true, true,
        std::make_pair(1, 4),
        std::make_pair(1, 1),
        {std::make_pair(3, 2)});   // pit at destination
    world.move_forward();
    REQUIRE(world.get_agent_is_alive() == false);
}

TEST_CASE("Moving into a living wumpus kills the agent", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld(std::make_pair(2, 2),
        "East", true, true,
        std::make_pair(3, 2),   // wumpus at destination
        std::make_pair(1, 1),
        {std::make_pair(4, 4)});
    world.move_forward();
    REQUIRE(world.get_agent_is_alive() == false);
}

TEST_CASE("Moving into a dead wumpus does not kill the agent", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld(std::make_pair(2, 2),
        "East", true, false,   // wumpus_alive = false
        std::make_pair(3, 2),  // wumpus at destination
        std::make_pair(1, 1),
        {std::make_pair(4, 4)});
    world.move_forward();
    REQUIRE(world.get_agent_is_alive() == true);
}

/*
* grabbed tests
*/
TEST_CASE("Grabbed succeeds when standing on gold", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld(std::make_pair(2, 2),
        "East", true, true,
        std::make_pair(4, 4),
        std::make_pair(2, 2),   // gold at agent's location
        {std::make_pair(1, 1)});

    world.grabbed();

    REQUIRE(world.get_agent_has_gold() == true);
}

TEST_CASE("Grabbing gold removes glitter from percept", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld(std::make_pair(2, 2),
        "East", true, true,
        std::make_pair(4, 4),
        std::make_pair(2, 2),   // gold at agent's location
        {std::make_pair(1, 1)});

    REQUIRE(world.percept().glitter == true);  // before grabbing

    world.grabbed();

    REQUIRE(world.percept().glitter == false); // after grabbing
}

TEST_CASE("Grabbed does nothing when not standing on gold", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld(std::make_pair(2, 2),
        "East", true, true,
        std::make_pair(4, 4),
        std::make_pair(3, 3),   // gold elsewhere
        {std::make_pair(1, 1)});

    world.grabbed();

    REQUIRE(world.get_agent_has_gold() == false);
}

TEST_CASE("Grabbing twice is harmless", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld(std::make_pair(2, 2),
        "East", true, true,
        std::make_pair(4, 4),
        std::make_pair(2, 2),   // gold at agent's location
        {std::make_pair(1, 1)});

    world.grabbed();
    world.grabbed();   // second call should be a harmless no-op

    REQUIRE(world.get_agent_has_gold() == true);
}

/*
* climbed tests
*/
TEST_CASE("Climbing out succeeds at exit location", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld(std::make_pair(1, 1),   // at the exit
        "East", true, true,
        std::make_pair(4, 4),
        std::make_pair(2, 2),
        {std::make_pair(3, 3)});

    world.climbed();

    REQUIRE(world.get_has_climbed_out() == true);
}

TEST_CASE("Climbing does nothing away from exit location", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld(std::make_pair(2, 2),   // not at the exit
        "East", true, true,
        std::make_pair(4, 4),
        std::make_pair(3, 3),
        {std::make_pair(1, 4)});

    world.climbed();

    REQUIRE(world.get_has_climbed_out() == false);
}

TEST_CASE("Agent can climb out with the gold", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld(std::make_pair(1, 1),   // at the exit
        "East", true, true,
        std::make_pair(4, 4),
        std::make_pair(1, 1),   // gold at the exit square
        {std::make_pair(3, 3)});

    world.grabbed();
    world.climbed();

    REQUIRE(world.get_agent_has_gold() == true);
    REQUIRE(world.get_has_climbed_out() == true);
}

TEST_CASE("Agent can climb out without the gold", "[WumpusWorld]") {
    auto world = wumpus::WumpusWorld(std::make_pair(1, 1),   // at the exit
        "East", true, true,
        std::make_pair(4, 4),
        std::make_pair(3, 3),   // gold elsewhere
        {std::make_pair(2, 2)});

    world.climbed();

    REQUIRE(world.get_agent_has_gold() == false);
    REQUIRE(world.get_has_climbed_out() == true);
}