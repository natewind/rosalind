#ifndef IO_HPP
#define IO_HPP

#include <ios>         // std::ios_base
#include <tuple>
#include <string>      // std::string
#include <cctype>      // std::isspace
#include <istream>     // std::istream
#include <fstream>     // std::ifstream
#include <cstddef>     // std::ptrdiff_t, std::nullptr_t
#include <iostream>    // std::cin, std::cout
#include <string_view> // std::string_view
#include <type_traits> // std::is_same

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

template <class T = std::string, class... Ts>
auto read(std::istream &source = std::cin)
{
	if constexpr (sizeof...(Ts) == 0)
	{
		T x;
		source >> x;
		return x;
	}

	else return std::tuple { read<T>(source), read<Ts>(source)... };
}

class printer
{
	std::ostream &out;

public:
	constexpr printer(std::ostream &stream) : out(stream) {}

	template <class T = char const*, class... Args>
	constexpr void operator()(T const &value = "", Args const&... args)
	{
		if constexpr (std::is_same<T, bool>::value)
			out << (value ? "True" : "False");
		else
			out << value;

		if constexpr (sizeof...(Args) > 0)
		{
			out << ' ';
			(*this)(args...);
		}

		else out << '\n';
	}
};

inline namespace open_modes
{
	constexpr auto append   = std::ios_base::app;
	constexpr auto binary   = std::ios_base::binary;
	constexpr auto mode_read     = std::ios_base::in; // TODO
	constexpr auto write    = std::ios_base::out;
	constexpr auto truncate = std::ios_base::trunc;
	constexpr auto at_end   = std::ios_base::ate;
}

class open
{
	std::fstream stream;
	using openmode = std::ios_base::openmode;

public:
	printer print;

	open(std::string const &filename, openmode mode = mode_read)
		: print(stream) { stream.open(filename, mode); }

	constexpr auto begin() { return ifstream_iterator(stream); }
	constexpr auto end() { return nullptr; }

	template <class... Ts>
	auto read() { return ::read<Ts...>(stream); }
};

#endif
