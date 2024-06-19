cmake_minimum_required(VERSION 3.25)

project(sarhlib
	VERSION 0.1.0 
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wshadow -Wpedantic)
# C++ only -Wnon-virtual-dtor 

add_subdirectory(src/sarhc)
add_subdirectory(src/safequeue)
add_subdirectory(src/socket)
add_subdirectory(src/split)

enable_testing()
add_subdirectory(tests)
add_subdirectory(templates)