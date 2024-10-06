cmake_minimum_required(VERSION 3.28)
project(DataStructures)

set(CMAKE_CXX_STANDARD 23)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

add_executable(DataStructures main.cpp
        src/BinarySearchTree.cpp
        src/Node.cpp)

target_include_directories(DataStructures PUBLIC include)