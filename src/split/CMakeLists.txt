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

# find_program(CLANG_TIDY clang-tidy)
# if(CLANG_TIDY)
#     set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#     add_custom_target(
#         split-tidy
#         COMMAND ${CLANG_TIDY}
# 		-header-filter=${PROJECT_SOURCE_DIR}/include;
# 		-checks=-*
# 		-checks=bugprone-*
# 		-checks=cert-*
# 		-checks=concurrency-*
# 		-checks=cppcoreguidelines-*
# 		-checks=darwin-*
# 		-checks=misc-*
# 		-checks=modernize-*,-modernize-use-trailing-return-type
# 		-checks=performance-*
# 		-checks=portability-*
# 		-checks=readability-*
# 		-extra-arg=-Wno-unknown-warning-option
#         -extra-arg=-Wno-ignored-optimization-argument
#         -extra-arg=-Wno-unused-command-line-argument
# 		-warnings-as-errors=*
# 		-extra-arg=-std=c++${CMAKE_CXX_STANDARD}
#         -p .
#         ${PROJECT_SOURCE_DIR}/src/split.cpp
#     )
# endif()

enable_testing()
add_subdirectory(tests)