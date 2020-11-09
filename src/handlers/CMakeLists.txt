cmake_minimum_required(VERSION 3.8)

set(handlers_headers
    FileHandler.h
    MessageHandler.h
    Handler_templ.h
)
set(handlers_sources
    FileHandler.cpp
    MessageHandler.cpp
    Handler_templ.cpp
)
set(handlers_includes
    include/HandlersExceptions.h
)

add_library(Handlers-lib ${handlers_headers} ${handlers_sources} ${handlers_includes})
target_include_directories(Handlers-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(Handlers-includes INTERFACE)
target_include_directories(Handlers-includes INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
