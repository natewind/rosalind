#ifndef IO_HPP
#define IO_HPP

#include <tuple>    // std::tuple
#include <cctype>   // std::isspace
#include <istream>  // std::istream
#include <fstream>  // std::fstream
#include <cstddef>  // std::ptrdiff_t, std::nullptr_t
#include <iterator> // std::input_iterator_tag

class istream_iterator
{
protected:
	std::istream &in;

	// TODO: Iterate through chars without reading everything twice!
	void skip_ws(char stop = '\n')
	{
		for (char c; (c = in.peek()) != stop && std::isspace(c); in.get());
	}

public:
	constexpr istream_iterator(std::istream &stream) : in(stream) {}

	template <class T>
	operator T()
	{
		T res;
		in >> res;
		skip_ws();
		return res;
	}

	operator char() { return in.get(); }

	using value_type = istream_iterator;
	using difference_type = std::ptrdiff_t;
	using pointer = istream_iterator *;
	using reference = istream_iterator &;
	using iterator_category	= std::input_iterator_tag;

	bool operator==(std::nullptr_t) const { return in.peek() == '\n'; }

	bool operator!=(std::nullptr_t end) const { return !(*this == end); }

	constexpr auto operator++() const { return *this; }
	constexpr auto operator*() const { return *this; }

	// Dummies to satisfy Iterator requirements
	constexpr auto operator++(int) const { return *this; }
	constexpr auto operator->() const { return this; }
};

struct ifstream_iterator : public istream_iterator
{
	using istream_iterator::istream_iterator;

	template <class T>
	operator T()
	{
		T res;
		in >> res;
		skip_ws(EOF);
		return res;
	}

	operator char() { return in.get(); }

	using value_type = ifstream_iterator;
	using pointer = ifstream_iterator *;
	using reference = ifstream_iterator &;

	bool operator==(std::nullptr_t) const { return in.peek() == EOF; }

	bool operator!=(std::nullptr_t end) const { return !(*this == end); }

	constexpr auto operator++() const { return *this; }
	constexpr auto operator*() const { return *this; }

	// Dummies to satisfy Iterator requirements
	constexpr auto operator++(int) const { return *this; }
	constexpr auto operator->() const { return this; }
};

class open
{
	std::fstream stream;

public:
	open(char const *filename) { stream.open(filename); }

	constexpr auto begin() { return ifstream_iterator(stream); }
	constexpr auto end() { return nullptr; }

	template <class T, class... Ts>
	constexpr auto read()
	{
		if constexpr (sizeof...(Ts) == 0)
		{
			T x;
			stream >> x;
			return x;
		}

		else return std::tuple { read<T>(), read<Ts>()... };
	}

	template <class T, class... Ts>
	constexpr void print(T const &x, Ts const&... xs)
	{
		stream << x;
		((stream << " " << xs), ...);
		stream << '\n';
	}
};

#endif
