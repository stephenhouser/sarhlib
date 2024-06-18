#ifndef SARH_SPLIT_H
#define SARH_SPLIT_H

#include <string>
#include <vector>

namespace sarh {

std::vector<std::string_view> split_loop(
	const std::string_view &src,
	char delimiter);

}

#endif	// SARH_SPLIT_H