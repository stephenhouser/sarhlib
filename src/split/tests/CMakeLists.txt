
include(FetchContent)

# Test Library/Framework
# [Catch2](https://github.com/catchorg/Catch2)
FetchContent_Declare(Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.6.0
  )
FetchContent_MakeAvailable(Catch2)

add_executable(sarh_tests 
	split_test.cpp
)

target_link_libraries(sarh_tests 
	PRIVATE
		Catch2::Catch2WithMain
)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)

enable_testing()
#catch_discover_tests(sarh_tests)
