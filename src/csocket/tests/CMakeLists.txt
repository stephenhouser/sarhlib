
# require C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# enable FetchContent
include(FetchContent)

# declare Catch2
FetchContent_Declare(Catch2                              # name of the content
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git  # the repository
  GIT_TAG        v2.13.4                                 # the tag
  )

# make available
FetchContent_MakeAvailable(Catch2)


list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
include(CTest)
include(Catch)

add_executable(client_tests client_tests.cpp)
target_link_libraries(client_tests
	PRIVATE
		lib::csocket
		Catch2::Catch2WithMain
)

enable_testing()
#add_test(test_all client_tests)
# define test
# add_test( 
# 	NAME catch_test
#   	COMMAND $<TARGET_FILE:cpp_test> --success
# )
catch_discover_tests(client_tests)


# if (CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
#   find_package(flex CONFIG REQUIRED)
# endif()

# include(CTest)
# include(Catch)

# # sets all nessary default things
# function(add_flex_test test_name)
#   cmake_path(GET CMAKE_CURRENT_LIST_DIR FILENAME module_name)

#   set(test_file "${test_name}_test.cpp")
#   set(test_target "${module_name}-${test_name}")

#   add_executable(${test_target} "${test_file}")

#   target_link_libraries(
#     ${test_target} PRIVATE flex::${module_name} Catch2::Catch2WithMain
#   )

#   catch_discover_tests(${test_target} TEST_PREFIX "${test_target}:" ${ARGN})