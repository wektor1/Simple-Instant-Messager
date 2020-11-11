cmake_minimum_required(VERSION 3.8)

set(test_sources
    test_FileHandler.cpp
    test_MessageHandler.cpp
    test_MessagesSenderManager.cpp
    test_MessagesReciverManager.cpp
)

add_library(Mocks-lib INTERFACE)
target_include_directories(Mocks-lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/mocks)

add_executable(${PROJECT_NAME}-ut ${test_sources})

target_include_directories(${PROJECT_NAME}-ut PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME}-ut gtest_main gmock_main
                      Handlers-lib Comunication-includes Managers-lib Mocks-lib)
