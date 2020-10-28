cmake_minimum_required(VERSION 3.5.1)
project(my_workshop)

add_subdirectory(utils)

include_directories(inc)
add_executable(my_workshop src/main.cpp src/workshop_system.cpp)

target_link_libraries (my_workshop LINK_PUBLIC linked_list record)