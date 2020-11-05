cmake_minimum_required(VERSION 3.5.1)
project(InputHandler)
include_directories(include ../utils/socketcan_cpp)

add_executable(main src/InputReader.cpp
                    src/Main.cpp 
                    ../utils/socketcan_cpp/socketcan.cpp)
target_link_libraries(main PUBLIC X11)
