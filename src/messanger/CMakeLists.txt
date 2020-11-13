cmake_minimum_required(VERSION 3.8)

set(messanger_headers
    Chat.h
    ChatUI.h
    Loger.h
)
set(messanger_sources
    Chat.cpp
    ChatUI.cpp
    Loger.cpp
)

add_library(Messanger-includes INTERFACE)
target_include_directories(Messanger-includes INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(Messanger-lib ${messanger_headers} ${messanger_sources})
target_include_directories(Messanger-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Messanger-lib PUBLIC Timer-includes Messanger-includes Managers-includes Comunication-includes)
