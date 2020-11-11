cmake_minimum_required(VERSION 3.5.1)
project(OutputHandler)
include_directories(include ../utils/include)

add_executable(output_handler 
                    src/main.cpp 
                    ../utils/src/can_buffer.cpp
                    ../utils/src/can_reader.cpp
                    ../utils/src/socketcan.cpp)
target_link_libraries(output_handler PUBLIC pthread)
#set(CMAKE_BUILD_TYPE Debug)
