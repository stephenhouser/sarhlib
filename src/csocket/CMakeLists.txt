cmake_minimum_required(VERSION 3.15)

project (socket)

add_library(${PROJECT_NAME} src/socket.cpp src/serversocket.cpp src/tcpsocket.cpp)
add_library(lib::csocket ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
    lib::safequeue
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

add_subdirectory(examples)

enable_testing()
add_subdirectory(tests)