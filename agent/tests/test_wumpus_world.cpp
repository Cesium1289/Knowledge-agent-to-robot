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