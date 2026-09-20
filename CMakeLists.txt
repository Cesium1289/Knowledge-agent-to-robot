cmake_minimum_required(VERSION 3.16)
project(wumpus_world_systems CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

add_compile_options(-Wall -Wextra)

# Stage 1
add_subdirectory(agent)

# Stage 2/3 — uncomment once the server exists
# add_subdirectory(server)
