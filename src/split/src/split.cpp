
#if !defined(SARH_SPLIT_FAST)
#define SARH_SPLIT_FAST true
#endif

#include <string>

#if !defined(SARH_SPLIT_FAST)
#include <ranges>
#endif

#include "split.h"

namespace sarh {

#if defined(SARH_SPLIT_FAST)

// Split string_view on delimiter and return vector of string_views
std::vector<std::string_view> split_loop(const std::string_view &src, char delim) {
	std::vector<std::string_view> result;

	size_t start = 0, end = 0;
	while (end != std::string::npos) {
		end = src.find(delim, start);

		std::string_view token = src.substr(start, (end - start));
		if (!token.empty()) {
			result.push_back(token);
		}

		start = end + 1;
	}

	return result;
}

#else

std::vector<std::string_view> split_range(const std::string_view &words, char delim) {
	std::vector<std::string_view> result;

	for (const auto &word : words | std::views::split(delim)) {
		result.push_back(std::string_view(word.begin(), word.end()));
	}

	return result;
}

#endif	// SARH_SPLIT_FAST
}  // namespace sarh