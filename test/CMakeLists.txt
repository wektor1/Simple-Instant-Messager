cmake_minimum_required(VERSION 3.8)

file(GLOB_RECURSE test_sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(${PROJECT_NAME}-ut ${test_sources})

target_link_libraries(${PROJECT_NAME}-ut gtest)
target_link_libraries(${PROJECT_NAME}-ut Handlers-lib)
target_link_libraries(${PROJECT_NAME}-ut Comunication-lib)
