cmake_minimum_required(VERSION 3.5.1)
project(InputHandler)
include_directories(include ../utils/include)

add_executable(input_handler src/keyboard_input_reader.cpp
                    src/main.cpp 
                    ../utils/src/socketcan.cpp)
target_link_libraries(input_handler PUBLIC X11 pthread)
#set(CMAKE_BUILD_TYPE Debug)
