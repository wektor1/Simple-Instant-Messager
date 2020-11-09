cmake_minimum_required(VERSION 3.8)

set(managers_headers
    MessagesSenderManager.h
)
set(managers_sources
    MessagesSenderManager.cpp
)

add_library(Managers-lib ${managers_headers} ${managers_sources})
target_include_directories(Managers-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Managers-lib PUBLIC Comunication-includes Handlers-includes)
