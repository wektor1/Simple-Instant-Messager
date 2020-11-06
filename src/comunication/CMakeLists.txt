cmake_minimum_required(VERSION 3.8)

file(GLOB_RECURSE comunication_headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB_RECURSE comunication_sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(Comunication-lib ${comunication_headers} ${comunication_sources})

find_package(Boost COMPONENTS date_time)
target_link_libraries(Comunication-lib PUBLIC ${Boost_SYSTEM_LIBRARY})

target_include_directories(Comunication-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
