cmake_minimum_required(VERSION 3.5.1)
project(InputHandler)
include_directories(include ../utils/socketcan_cpp)

add_executable(main src/keyboard_input_reader.cpp
                    src/main.cpp 
                    ../utils/socketcan_cpp/socketcan.cpp)
target_link_libraries(main PUBLIC X11 pthread)
#set(CMAKE_BUILD_TYPE Debug)
