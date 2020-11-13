cmake_minimum_required(VERSION 3.8)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(timer)
add_subdirectory(handlers)
add_subdirectory(comunication)
add_subdirectory(managers)
add_subdirectory(messanger)

target_link_libraries(${PROJECT_NAME} Timer-lib)
target_link_libraries(${PROJECT_NAME} Handlers-lib)
target_link_libraries(${PROJECT_NAME} Comunication-lib)
target_link_libraries(${PROJECT_NAME} Managers-lib)
target_link_libraries(${PROJECT_NAME} Messanger-lib)
