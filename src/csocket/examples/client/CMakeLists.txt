cmake_minimum_required(VERSION 3.15)

project(client)

add_executable(${PROJECT_NAME} client.cpp)
target_link_libraries(${PROJECT_NAME}
    lib::csocket
    lib::safequeue
)