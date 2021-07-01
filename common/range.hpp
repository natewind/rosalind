#ifndef RANGE_HPP
#define RANGE_HPP

#include <iterator> // std::input_iterator_tag

template <class Int = int>
class range
{
	Int start;
	Int const stop, step;

public:
	constexpr range(Int start, Int stop, Int step = 1)
		: start(start), stop(stop), step(step) {}

	constexpr range(Int stop) : range(0, stop) {}
	constexpr range(range const &) = default;

	using value_type = Int;
	using difference_type = value_type;
	using pointer = value_type *;
	using reference = value_type &;
	using iterator_category	= std::input_iterator_tag;

	constexpr bool operator==(range const &other) const
	{
		bool res = (start == other.start);
		if (step > 0)
			res |= (start >= stop && other.start >= stop);
		else
			res |= (start <= stop && other.start <= stop);
		return res;
	}

	constexpr bool operator!=(range const &other) const
	{
		return !(*this == other);
	}

	constexpr range operator++()
	{
		start += step;
		return *this;
	}

	constexpr range operator++(int)
	{
		range old = *this;
		start += step;
		return old;
	}

	constexpr value_type operator*() const { return start; }

	// A dummy to satisfy Iterator requirements
	constexpr value_type const* operator->() const { return &start; }

	constexpr auto begin() { return *this; }
	constexpr auto   end() { return range(stop, stop, step); }
};

#endif
