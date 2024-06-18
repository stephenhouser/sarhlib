cmake_minimum_required(VERSION 3.15)

project (safequeue)

add_library(${PROJECT_NAME} INTERFACE)
add_library(sarh::safequeue ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    INTERFACE
        ${PROJECT_SOURCE_DIR}/include
)