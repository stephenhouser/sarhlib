cmake_minimum_required(VERSION 3.15)

project(split)

add_library(${PROJECT_NAME} 
	src/split.cpp
)
add_library(sarh::split ALIAS ${PROJECT_NAME})

#target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
#target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

enable_testing()
add_subdirectory(tests)