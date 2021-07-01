#ifndef RANGE_HPP
#define RANGE_HPP

#include <iterator> // std::input_iterator_tag

class range
{
	using VT = int;
	VT start;
	VT const stop, step;

public:
	// TODO: Exception if step == zero?

	constexpr range(VT start, VT stop, VT step = 1)
		: start(start), stop(stop), step(step) {}

	constexpr range(VT stop) : range(0, stop) {}
	constexpr range(range const &) = default;

	using value_type = VT;
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
