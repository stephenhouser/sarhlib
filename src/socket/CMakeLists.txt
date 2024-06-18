cmake_minimum_required(VERSION 3.15)

project(socket)

add_library(${PROJECT_NAME} 
    src/socket.cpp 
    src/serversocket.cpp
    src/tcpsocket.cpp
)

add_library(sarh::socket ALIAS ${PROJECT_NAME})

# -Wno-vla don't warn about variable length arrays (C99 standard)
target_compile_options(${PROJECT_NAME} PRIVATE -Wno-vla)

target_link_libraries(${PROJECT_NAME}
    sarh::safequeue
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

add_subdirectory(examples)

enable_testing()
add_subdirectory(tests)