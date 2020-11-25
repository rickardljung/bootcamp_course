cmake_minimum_required(VERSION 3.5.1)
project(drivetrain)
include_directories(include ../utils/include)

add_executable(drivetrain
                    src/main.cpp
                    src/gearbox_simulator.cpp
                    src/engine_simulator.cpp)

target_link_libraries(drivetrain PUBLIC pthread can_lib)

add_subdirectory(test)

#set(CMAKE_BUILD_TYPE Debug)
