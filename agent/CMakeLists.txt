add_library(agent_lib
    src/wumpus_world.cpp
    src/wumpus_world_agent.cpp
    src/knowledge_base.cpp
)
target_include_directories(agent_lib PUBLIC include)

add_executable(wumpus_world_demo src/main.cpp)
target_link_libraries(wumpus_world_demo PRIVATE agent_lib)

# Tests wired up once a framework (e.g. Catch2 or GoogleTest) is added.
# add_subdirectory(tests)
