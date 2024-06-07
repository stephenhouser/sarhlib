cmake_minimum_required(VERSION 3.15)

project(discovery-test)

add_executable(${PROJECT_NAME} 
	discovery_test.cpp
)

target_link_libraries(${PROJECT_NAME}
	lib::flex
    lib::csocket
    lib::safequeue
)