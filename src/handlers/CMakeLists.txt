cmake_minimum_required(VERSION 3.8)

file(GLOB_RECURSE handlers_headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

file(GLOB_RECURSE handlers_sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(Handlers-lib ${handlers_headers} ${handlers_sources})

target_include_directories(Handlers-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
