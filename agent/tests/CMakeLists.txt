include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.7.1
)
FetchContent_MakeAvailable(Catch2)

add_executable(agent_tests
    test_wumpus_world.cpp
)
target_link_libraries(agent_tests PRIVATE agent_lib Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(agent_tests)