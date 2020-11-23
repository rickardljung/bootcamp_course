cmake_minimum_required(VERSION 3.5.1)
project(drivetrain)
include_directories(include ../utils/include)

add_executable(drivetrain
                    src/main.cpp
                    src/gearbox_simulator.cpp
                    src/engine_simulator.cpp

                    ../utils/src/can_buffer.cpp
                    ../utils/src/can_io_thread.cpp
                    ../utils/src/socketcan.cpp)
target_link_libraries(drivetrain PUBLIC pthread)
#set(CMAKE_BUILD_TYPE Debug)
