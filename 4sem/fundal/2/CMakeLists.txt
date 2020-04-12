project(2)
cmake_minimum_required(VERSION 2.8)

find_package(Boost )
IF (Boost_FOUND)
    include_directories(SYSTEM ${Boost_INCLUDE_DIR})
    set (Boost_USE_STATIC_LIBS OFF) # enable dynamic linking
    set (Boost_USE_MULTITHREAD ON)  # enable multithreading
    find_package (Boost COMPONENTS REQUIRED chrono date_time)


endif()
add_executable(1 1/main.cpp)
add_executable(2 2/main.cpp)
add_executable(4 4/main.cpp 4/RBTree.h 4/Entry.h)


target_link_libraries (4 ${Boost_LIBRARIES})