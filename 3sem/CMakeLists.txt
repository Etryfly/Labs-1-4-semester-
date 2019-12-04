cmake_minimum_required(VERSION 3.6)
project(fundal)
#set(CMAKE_CXX_STANDARD fundal/11)
add_executable(fundal fundal/3/12/main.c)
#add_executable(server OS/socket/server/server.c)
#add_executable(client OS/socket/client/client.c)

target_link_libraries(fundal m)
