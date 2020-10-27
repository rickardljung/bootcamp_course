cmake_minimum_required(VERSION 3.5.1)
project(my_workshop)

add_library(linked_list SHARED src/linked_list.cpp)

target_include_directories(linked_list PUBLIC inc)
