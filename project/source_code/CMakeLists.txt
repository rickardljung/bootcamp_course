cmake_minimum_required(VERSION 3.5.1)

add_subdirectory(drivetrain)
add_subdirectory(input_handler)
add_subdirectory(output_handler)
add_subdirectory(utils/output_panel)
add_subdirectory(utils/googletest) # add googletest subdirectory

include_directories(utils/googletest/include) # this is so we can #include <gtest/gtest.h>