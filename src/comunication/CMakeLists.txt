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
set(comunication_includes
    include/ClientInterface.h
    include/ServerInterface.h
    include/ComunicationExceptions.h
)

add_library(Comunication-lib  ${comunication_headers} ${comunication_sources} ${comunication-includes})
find_package(Boost COMPONENTS date_time)
target_link_libraries(Comunication-lib PUBLIC ${Boost_SYSTEM_LIBRARY})
target_include_directories(Comunication-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(Comunication-includes INTERFACE)
target_include_directories(Comunication-includes INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
