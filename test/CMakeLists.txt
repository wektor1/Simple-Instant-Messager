cmake_minimum_required(VERSION 3.8)

set(test_sources
    test_FileHandler.cpp
    test_MessageHandler.cpp
    test_MessagesSenderManager.cpp
)

add_executable(${PROJECT_NAME}-ut ${test_sources})

target_include_directories(${PROJECT_NAME}-ut PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME}-ut gtest_main)
target_link_libraries(${PROJECT_NAME}-ut gmock_main)
target_link_libraries(${PROJECT_NAME}-ut Handlers-lib)
target_link_libraries(${PROJECT_NAME}-ut Comunication-includes)
target_link_libraries(${PROJECT_NAME}-ut Managers-lib)
