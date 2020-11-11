cmake_minimum_required(VERSION 3.8)

set(comunication_headers
    MessageReciveServer.h
    MessageSendClient.h
    MessagesDefinitions.h
)
set(comunication_sources
    MessageReciveServer.cpp
    MessageSendClient.cpp
)
set(Boost_USE_MULTITHREAD ON)

add_library(Comunication-includes INTERFACE)
target_include_directories(Comunication-includes INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(Comunication-lib  ${comunication_headers} ${comunication_sources})
find_package(Boost COMPONENTS system thread regex)
target_link_libraries(Comunication-lib PUBLIC ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} Comunication-includes)
target_include_directories(Comunication-lib PUBLIC ${Boost_INCLUDE_DIRS} ${Boost_LIBRARY_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})
