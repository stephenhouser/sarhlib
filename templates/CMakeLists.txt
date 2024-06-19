
include(FetchContent)

# Test Library/Framework
# [Catch2](https://github.com/catchorg/Catch2)
FetchContent_Declare(Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.6.0
  )
FetchContent_MakeAvailable(Catch2)

find_program(CLANG_TIDY clang-tidy)
if(CLANG_TIDY)
	set(CMAKE_CXX_CLANG_TIDY 
		${CLANG_TIDY}
		-header-filter=.;
		-checks=-*
		-checks=bugprone-*
		-checks=cert-*
		-checks=concurrency-*
		-checks=cppcoreguidelines-*
		-checks=darwin-*
		-checks=misc-*
		-checks=modernize-*,-modernize-use-trailing-return-type
		-checks=performance-*
		-checks=portability-*
		-checks=readability-*
		-extra-arg=-Wno-unknown-warning-option
        -extra-arg=-Wno-ignored-optimization-argument
        -extra-arg=-Wno-unused-command-line-argument
		-warnings-as-errors=*
		-extra-arg=-std=c++${CMAKE_CXX_STANDARD}
        -p
	)
endif()

# set(CMAKE_CXX_CLANG_TIDY 
# 	clang-tidy;
# 	-header-filter=.;
# 	-checks=*,-llvmlibc-*,-fuchsia-*,-altera-*;
# 	-warnings-as-errors=*;
# )

add_executable(template-c17
	template-c17.cpp
)

target_compile_options(template-c17 PRIVATE -fsanitize=address,leak,undefined)
target_link_options(template-c17 PRIVATE -fsanitize=address,leak,undefined)

target_link_libraries(template-c17
	PRIVATE		
		Catch2::Catch2
)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)

enable_testing()
#catch_discover_tests(template-c17)

