cmake_minimum_required(VERSION 3.15)

project (flex)

add_library(${PROJECT_NAME} src/discovery.cpp)
add_library(lib::flex ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

enable_testing()
add_subdirectory(tests)
