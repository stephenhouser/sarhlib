cmake_minimum_required(VERSION 3.15)

project(sarhc)

add_library(${PROJECT_NAME} 
	src/array.c
	src/list.c
	src/queue.c
	src/read_line.c
	src/stack.c
	src/strings.c
)
add_library(sarh::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

#target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
#target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

#enable_testing()
#add_subdirectory(tests)