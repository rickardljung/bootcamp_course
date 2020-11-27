cmake_minimum_required(VERSION 3.5.1)
project(InputHandler)
include_directories(include ../utils/include)

add_executable(input_handler    src/main.cpp)

target_link_libraries(input_handler PUBLIC X11 pthread can_lib)
