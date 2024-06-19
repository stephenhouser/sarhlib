/* template - Template code for C++17 Program
 *
 * 2017/10/01 Stephen Houser
 */
#include <getopt.h>

#include <algorithm>  // std::transform
// #include <cerrno>	  // integer range errors
#include <chrono>  // for high_resolution_clock
// #include <cstdlib>
#include <iostream>	 // cout
// #include <numeric>
#include <string>  // general string stuff
#include <vector>  // vectors

const char *const program_name = "template";

void usage(const char *p_name = nullptr) {
	const char *l_name = p_name != nullptr ? p_name : program_name;
	std::cout << "Template Program\n";
	std::cout << "\n";
	std::cout << "usage: " << l_name << " [-h] [-v] >] [<argument>...]\n";
	std::cerr << "\t-h\tprint help and usage\n";
	std::cerr << "\t-v\tprint verbose messages\n";
	std::cerr << "\t<argument>...\tstrings to print out...\n";
	std::cerr << "\n";
}

int main(int argc, char *argv[]) {
	bool verbose = false;				 // show progress and debug information
	int option_char = '\0';				 // getopt returned option character
	std::vector<std::string_view> arguments;	 // arguments to print out

	const auto start = std::chrono::high_resolution_clock::now();

	while ((option_char = getopt(argc, argv, "?hv")) != EOF) {
		switch (option_char) {
			case '?':
			case 'h':
				usage(argv[0]);
				return 0;
			case 'v':
				verbose = true;
				break;
			default:
				break;
		}
	}

	// Parse remaining command line arguments (numbers) for what numbers to find
	// lambda that takes a char * and returns std::string
	std::transform(&argv[optind], &argv[argc], std::back_inserter(arguments),
				   [](char *arg) -> std::string_view {
					   return std::string_view { arg };
				   });

	if (verbose) {
		std::cout << "There were " << arguments.size() << " arguments passed.\n";
	}

	if (arguments.empty()) {
		usage(argv[0]);
	} else {
		for (const auto &arg : arguments) {
			if (verbose) {
				std::cout << "[";
			}
			std::cout << arg;
			if (verbose) {
				std::cout << "]";
			}
			std::cout << "\n";
		}
	}

	const auto finish = std::chrono::high_resolution_clock::now();
	if (verbose) {
		std::chrono::duration<double> elapsed = finish - start;
		std::cout << " elapsed time: " << elapsed.count() << "s\n";
	}
}