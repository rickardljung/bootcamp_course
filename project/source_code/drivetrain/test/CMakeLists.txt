cmake_minimum_required(VERSION 3.5.1)
project(drivetrain_tests)

add_executable(engine_test engine/engine_test.cpp ../src/engine_simulator.cpp)

include_directories(utils/googletest/include ../include) # this is so we can #include <gtest/gtest.h>

target_link_libraries(engine_test PRIVATE gtest) # link google test to this executable

