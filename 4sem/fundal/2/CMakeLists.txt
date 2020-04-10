project(2)
cmake_minimum_required(VERSION 2.8)

find_package(Boost)



add_executable(1 1/main.cpp)
add_executable(2 2/main.cpp)
add_executable(4 4/main.cpp 4/RBTree.h 4/Entry.cpp 4/Entry.h)
