
include(FetchContent)

# Test Library/Framework
# [Catch2](https://github.com/catchorg/Catch2)
FetchContent_Declare(Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.6.0
  )
FetchContent_MakeAvailable(Catch2)

add_executable(template-c17
	template-c17.cpp
)

target_link_libraries(template-c17
	PRIVATE		
		Catch2::Catch2
)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)

enable_testing()
#catch_discover_tests(template-c17)

