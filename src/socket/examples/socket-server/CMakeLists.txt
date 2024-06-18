cmake_minimum_required(VERSION 3.15)

project(socket-server)

add_executable(${PROJECT_NAME} server.cpp)
target_link_libraries(${PROJECT_NAME}
    sarh::socket
    sarh::safequeue
)