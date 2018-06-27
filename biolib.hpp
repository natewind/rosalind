#ifndef BIOLIB_HPP
#define BIOLIB_HPP

#include <tuple>
#include <string>
#include <iterator>
#include <algorithm>

namespace bio
{
	constexpr char TU_swap(char c)
	{
		return (c == 'T') ? 'U' : (c == 'U') ? 'T' : c;
	}

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
	protected:
		Strand &self = *this;

	public:
		using std::string::string;

		inline auto Count()
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
	};

	class DNA : public Strand
	{
		static constexpr char alphabet[] = "ACGT";

	public:
		using Strand::Strand;
		inline bool IsValid() { return is_valid(self, alphabet); }
	};

	class RNA : public Strand
	{
		static constexpr char alphabet[] = "ACGU";

	public:
		using Strand::Strand;
		inline bool IsValid() { return is_valid(self, alphabet); }
	};
}

#endif
