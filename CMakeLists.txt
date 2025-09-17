cmake_minimum_required(VERSION 3.31)
project(Maze_Generator_V2)

set(CMAKE_CXX_STANDARD 20)

find_package(raylib CONFIG REQUIRED)

add_executable(Maze_Generator_V2 main.cpp
        MazeData.cpp
        MazeData.h
        CellAndWallData.cpp
        CellAndWallData.h
        MazeOperations.cpp
        MazeOperations.h
        VerifyInput.cpp
        VerifyInput.h
)

#Dijkstras Path Algorithm

if (TARGET raylib::raylib)
    target_link_libraries(Maze_Generator_V2 PRIVATE raylib::raylib)
else()
    target_link_libraries(Maze_Generator_V2 PRIVATE raylib)
endif()