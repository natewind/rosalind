#ifndef UTILS_HPP
#define UTILS_HPP

// #include <tuple>
// #include <string>
// #include <iterator>
// #include <stdexcept>
// #include <algorithm>
// #include <string_view>
// #include <unordered_map>
// #include "range.hpp"

constexpr auto pct(float frac) -> float { return 100 * frac; }

// TODO: Rename to lucas_sequence(n, p = 1, q = -1)
constexpr auto fibonacci(int n, int a = 1, int b = 1) -> long
{
	long sum[2] = {1, 1};

	for (auto i : range(3, n + 1))
	{
		auto j = bool(i & 1);
		sum[j] = a * sum[j] + b * sum[!j];
	}

	return sum[n & 1];
}

#endif
