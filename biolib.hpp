#ifndef BIOLIB_HPP
#define BIOLIB_HPP

#include <tuple>
#include <string>
#include <iterator>
#include <algorithm>

namespace bio
{
	template <typename T, typename U>
	constexpr bool contains(const T &self, U value)
	{
		using std::find, std::begin, std::end;
		return find(begin(self), end(self), value) != end(self);
	}

	template <typename T, typename U>
	inline bool is_valid(const T &self, const U &abc)
	{
		for (auto c : self)
			if (!contains(abc, c))
				return false;

		return true;
	}

	class Strand : public std::string
	{
		Strand &self = *this;

	public:
		using std::string::string;
		inline auto Count();
	};

	class RNA;

	class DNA : public Strand
	{
		Strand &self = *this;
		static constexpr char alphabet[] = "ACGT";

	public:
		using Strand::Strand;
		inline DNA(const RNA &other);
		inline bool IsValid() { return is_valid(self, alphabet); }
	};

	class RNA : public Strand
	{
		Strand &self = *this;
		static constexpr char alphabet[] = "ACGU";

	public:
		using Strand::Strand;
		inline RNA(const DNA &other);
		inline bool IsValid() { return is_valid(self, alphabet); }
	};

	//=========================Definitions:====================================

	inline auto Strand::Count()
	{
		int N[4] = {0};

		for (auto c : self)
		{
			switch (c)
			{
				case 'A': ++N[0]; break;
				case 'C': ++N[1]; break;
				case 'G': ++N[2]; break;
				default : ++N[3]; break;
			}
		}

		return std::make_tuple(N[0], N[1], N[2], N[3]);
	}

	inline DNA::DNA(const RNA &other) : Strand(other)
	{
		for (auto &c : self)
			if (c == 'U')
				c = 'T';
	}

	inline RNA::RNA(const DNA &other) : Strand(other)
	{
		for (char &c : self)
			if (c == 'T')
				c = 'U';
	}
}

#endif
