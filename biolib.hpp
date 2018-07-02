#ifndef BIOLIB_HPP
#define BIOLIB_HPP

#include <tuple>
#include <string>
#include <iterator>
#include <stdexcept>
#include <algorithm>
#include <string_view>
#include <pythonized/range>

namespace bio
{
	//========================== Utilities: ===================================

	template <typename T, typename U>
	constexpr bool contains(const T &self, U value)
	{
		using std::begin, std::end;
		return std::find(begin(self), end(self), value) != end(self);
	}

	template <typename T, typename U>
	inline bool is_valid(const T &self, const U &abc)
	{
		for (auto c : self)
			if (!contains(abc, c))
				return false;

		return true;
	}

	constexpr char complement(char c)
	{
		switch (c)
		{
			case 'A': return 'T';
			case 'C': return 'G';
			case 'G': return 'C';
			case 'T': return 'A';
		}
	}

	constexpr float pct (float frac) { return 100 * frac; }

	constexpr long fibonacci(int n, int a = 1, int b = 1)
	{
		long sum[2] = {1, 1};

		for (auto i : py::range(3, n + 1))
		{
			bool j = i & 1;
			sum[j] = a * sum[j] + b * sum[!j];
		}

		return sum[n & 1];
	}

	//========================== Objects: =====================================

	class FASTA
	{
		std::string id, sequence;

	public:
		inline FASTA() = default;
		inline void Read(std::istream &stream);
		inline auto & Sequence() const { return sequence; }
		inline auto & Id() const { return id; }
	};

	class Strand : public std::string
	{
		Strand &self = *this;

	public:
		using std::string::string;
		inline Strand(const FASTA &record)
			: std::string(record.Sequence()) {}
		inline int Distance(const Strand &other) const;
		inline float ContentGC() const;
		inline auto Count() const;
	};

	class RNA;

	class DNA : public Strand
	{
		Strand &self = *this;
		static constexpr char alphabet[] = "ACGT";

	public:
		using Strand::Strand;
		inline DNA(const RNA &other);
		inline bool IsValid() const { return is_valid(self, alphabet); }
		inline DNA Complement() const;
	};

	class RNA : public Strand
	{
		Strand &self = *this;
		static constexpr char alphabet[] = "ACGU";

	public:
		using Strand::Strand;
		inline RNA(const DNA &other);
		inline bool IsValid() const { return is_valid(self, alphabet); }
	};

	//========================== Definitions: =================================

	inline void FASTA::Read(std::istream &stream)
	{
		if (stream.peek() != '>')
			throw std::domain_error("Not FASTA format");
		stream.get();
		std::getline(stream, id);

		std::string s;
		for (char c; (c = stream.peek()) != '>' && c != EOF; sequence += s)
			std::getline(stream, s);
	}

	inline int Strand::Distance(const Strand &other) const
	{
		int res = 0;
		auto i = std::begin(other);

		for (char c : self)
		{
			res += (c != *i);
			if (++i == std::end(other))
				break;
		}

		return res;
	}

	inline float Strand::ContentGC() const
	{
		auto count = std::count_if(begin(), end(),
			[](auto c) { return (c == 'G') || (c == 'C'); });
		return float(count) / length();
	}

	inline auto Strand::Count() const
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

	inline DNA DNA::Complement() const
	{
		DNA other(self.length(), 0);
		auto it = std::rbegin(self);
		for (auto &c : other)
			c = complement(*it++);
		return other;
	}
}

namespace std
{
	inline istream & operator>>(istream &stream, bio::FASTA &arg)
	{
		arg.Read(stream);
		return stream;
	}

	inline ostream & operator<<(ostream &stream, bio::FASTA &arg)
	{
		// TODO
		return stream;
	}
}

#endif
