
#include <iostream>
#include <vector>

// This seems to be required, at least for MSVS 2015 on Win7,
// using Catch2 v2.9.2
#if defined(_WIN32)
#define CATCH_CONFIG_DISABLE_EXCEPTIONS
#endif

#include <catch2/catch_all.hpp>

TEST_CASE("sahr::split header sanity check") {
	REQUIRE(true);
}

