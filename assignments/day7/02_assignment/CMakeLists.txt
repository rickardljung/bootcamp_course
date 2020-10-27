cmake_minimum_required(VERSION 3.5.1)
project(my_workshop)

add_subdirectory(utils)

include_directories(inc) #utils/linked_list/inc utils/record/inc)
add_executable(my_workshop src/main.cpp src/workshop_system.cpp)

#add_dependencies(my_workshop)
