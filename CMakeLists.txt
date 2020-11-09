cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER "g++")

project (InstantMessenger)

add_subdirectory(src)
add_subdirectory(external)
add_subdirectory(test)
