cmake_minimum_required(VERSION 3.8)

set(timer_sources
    Timer.cpp
)

add_library(Timer-includes INTERFACE)
target_include_directories(Timer-includes INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(Timer-lib ${timer_sources})
target_include_directories(Timer-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Timer-lib PUBLIC Timer-includes)
