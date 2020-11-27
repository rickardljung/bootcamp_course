cmake_minimum_required(VERSION 3.5.1)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_library(can_lib SHARED src/can_buffer.cpp src/socketcan.cpp)

target_include_directories(can_lib PUBLIC include)

target_link_libraries(can_lib PUBLIC pthread)

add_subdirectory(output_panel)
add_subdirectory(googletest)
