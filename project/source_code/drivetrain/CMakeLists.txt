cmake_minimum_required(VERSION 3.5.1)
project(drivetrain)
include_directories(include ../utils/socketcan_cpp)

add_executable(drivetrain src/can_buffer.cpp
                    src/main.cpp
                    src/vehicle.cpp
                    src/can_reader.cpp
                    src/gearbox_simulator.cpp
                    src/engine_simulator.cpp

                    ../utils/socketcan_cpp/socketcan.cpp)
target_link_libraries(drivetrain PUBLIC pthread)
