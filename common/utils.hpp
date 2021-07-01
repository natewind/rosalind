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

template <class Range, class T>
constexpr auto contains(Range const &range, T value) -> bool
{
	using std::begin, std::end;
	return std::find(begin(range), end(range), value) != end(range);
}

template <class Range1, class Range2>
auto is_valid(Range1 const &str, Range2 const &alphabet) -> bool
{
	return std::all_of
	(
		std::begin(str), std::end(str),
		[&alphabet](auto const c) { return contains(alphabet, c); }
	);
}

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
