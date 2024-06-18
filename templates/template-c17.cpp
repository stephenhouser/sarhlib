/* template - Template code for C++17 Program
 *
 * 2017/10/01 Stephen Houser
 */
#include <unistd.h>	 // getopt

#include <cerrno>  // integer range errors
#include <cstdlib>
#include <iostream>	 // cout
#include <numeric>
#include <string>  // general string stuff
#include <vector>  // vectors

bool verbose = false;  // show progress and debug information
const char *program_name = "template";

void usage(const char *p_name = NULL) {
	const char *l_name = p_name ? p_name : program_name;
	std::cout << "Template Program\n";
	std::cout << "\n";
	std::cout << "usage: " << l_name << " [-h] [-v] >] [<argument>...]\n";
	std::cerr << "\t-h\tprint help and usage\n";
	std::cerr << "\t-v\tprint verbose messages\n";
	std::cerr << "\t<argument>...\tstrings to print out...\n";
	std::cerr << "\n";
}

int main(int argc, char *argv[]) {
	int option_char;					 // getopt returned option character
	std::vector<std::string> arguments;	 // arguments to print out

	while ((option_char = getopt(argc, argv, "?hv")) != EOF) {
		switch (option_char) {
			case '?':
			case 'h':
				usage();
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
				   [](char *s) -> std::string {
					   return std::string(s);
				   });

	if (verbose) {
		std::cout << "There were " << arguments.size() << " arguments passed.\n";
	}

	if (arguments.size() == 0) {
		//usage();
	} else {
		for (auto n : arguments) {
			if (verbose) {
				std::cout << "[";
			}
			std::cout << n;
			if (verbose) {
				std::cout << "]";
			}
			std::cout << "\n";
		}
	}
}