cmake_minimum_required(VERSION 3.5.1)
project(my_workshop)

add_library(record SHARED src/record.cpp)

target_include_directories(record PUBLIC inc)