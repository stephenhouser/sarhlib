
add_executable(client_tests client_tests.cpp)
target_link_libraries(client_tests
	lib::csocket
)

add_test(test_all client_tests)