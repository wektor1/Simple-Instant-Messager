cmake_minimum_required(VERSION 3.8)

set(managers_headers
    MessagesSenderManager.h
    MessagesReciverManager.h
)
set(managers_sources
    MessagesSenderManager.cpp
    MessagesReciverManager.cpp
)

add_library(Managers-includes INTERFACE)
target_include_directories(Managers-includes INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(Managers-lib ${managers_headers} ${managers_sources})
target_include_directories(Managers-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Managers-lib PUBLIC Managers-includes Comunication-includes Handlers-includes)
