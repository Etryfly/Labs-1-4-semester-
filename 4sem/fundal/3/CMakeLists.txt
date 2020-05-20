cmake_minimum_required(VERSION 3.15)
project(1)
add_executable( 4 4/main.cpp 4/person.h)
add_executable( 1 1/main.cpp 1/Var.cpp)
add_executable( 2 2/main.cpp)
add_executable( 3 3/main.cpp)

find_package(jsoncpp CONFIG REQUIRED)
target_link_libraries(4 PRIVATE jsoncpp_lib)
