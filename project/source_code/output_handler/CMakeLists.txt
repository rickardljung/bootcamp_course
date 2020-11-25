cmake_minimum_required(VERSION 3.5.1)
project(OutputHandler)
include_directories(include ../utils/include)

add_executable(output_handler
                    src/main.cpp)

target_link_libraries(output_handler PUBLIC pthread canlib)
