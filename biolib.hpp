#ifndef BIOLIB_HPP
#define BIOLIB_HPP

#include <tuple>
#include <string>
#include <iterator>
#include <stdexcept>
#include <algorithm>
#include <string_view>
#include <unordered_map>
#include <pythonized/range>

namespace bio
{
	//========================== Utilities: ===================================

	template <typename T, typename U>
	constexpr auto contains(const T &range, U value) -> bool
	{
		using std::begin, std::end;
		return std::find(begin(range), end(range), value) != end(range);
	}

	template <typename T, typename U>
	inline auto is_valid(const T &self, const U &abc) -> bool
	{
		return std::all_of
		(
			std::begin(self), std::end(self),
			[&abc](const auto c) { return contains(abc, c); }
		);
	}

	constexpr auto complement(char c) -> char
	{
		switch (c)
		{
			case 'A': return 'T';
			case 'C': return 'G';
			case 'G': return 'C';
			case 'T': return 'A';
		}
	}

	constexpr auto pct(float frac) -> float { return 100 * frac; }

	constexpr auto fibonacci(int n, int a = 1, int b = 1) -> long
	{
		long sum[2] = {1, 1};

		for (auto i : py::range(3, n + 1))
		{
			auto j = bool(i & 1);
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
		inline auto Distance(const Strand &other) const -> int;
		inline auto ContentGC() const -> float;
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
		inline auto IsValid() const { return is_valid(self, alphabet); }
		inline auto Complement() const -> DNA;
	};

	class RNA : public Strand
	{
		Strand &self = *this;
		static constexpr char alphabet[] = "ACGU";

	public:
		using Strand::Strand;
		inline RNA(const DNA &other);
		inline auto IsValid() const { return is_valid(self, alphabet); }
	};

	class Protein : public std::string
	{
		// TODO
	public:
		inline Protein(const RNA &mRNA);
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

	inline auto Strand::Distance(const Strand &other) const -> int
	{
		auto res = int(0);
		auto i = std::begin(other);

		for (char c : self)
		{
			res += (c != *i);
			if (++i == std::end(other))
				break;
		}

		return res;
	}

	inline auto Strand::ContentGC() const -> float
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
		std::replace(std::begin(self), std::end(self), 'U', 'T');
	}

	inline RNA::RNA(const DNA &other) : Strand(other)
	{
		std::replace(std::begin(self), std::end(self), 'T', 'U');
	}

	inline auto DNA::Complement() const -> DNA
	{
		auto other = DNA();
		other.reserve(self.length());

		std::transform
		(
			std::rbegin(self), std::rend(self),
			std::back_inserter(other), complement
		);

		return other;
	}

	inline Protein::Protein(const RNA &mRNA)
	{
		static std::unordered_map<const char *, char> codons =
		{
			{ "UUU", 'F' }, { "CUU", 'L' }, { "AUU", 'I' }, { "GUU", 'V' },
			{ "UUC", 'F' }, { "CUC", 'L' }, { "AUC", 'I' }, { "GUC", 'V' },
			{ "UUA", 'L' }, { "CUA", 'L' }, { "AUA", 'I' }, { "GUA", 'V' },
			{ "UUG", 'L' }, { "CUG", 'L' }, { "AUG", 'M' }, { "GUG", 'V' },
			{ "UCU", 'S' }, { "CCU", 'P' }, { "ACU", 'T' }, { "GCU", 'A' },
			{ "UCC", 'S' }, { "CCC", 'P' }, { "ACC", 'T' }, { "GCC", 'A' },
			{ "UCA", 'S' }, { "CCA", 'P' }, { "ACA", 'T' }, { "GCA", 'A' },
			{ "UCG", 'S' }, { "CCG", 'P' }, { "ACG", 'T' }, { "GCG", 'A' },
			{ "UAU", 'Y' }, { "CAU", 'H' }, { "AAU", 'N' }, { "GAU", 'D' },
			{ "UAC", 'Y' }, { "CAC", 'H' }, { "AAC", 'N' }, { "GAC", 'D' },
			{ "UAA",  0  }, { "CAA", 'Q' }, { "AAA", 'K' }, { "GAA", 'E' },
			{ "UAG",  0  }, { "CAG", 'Q' }, { "AAG", 'K' }, { "GAG", 'E' },
			{ "UGU", 'C' }, { "CGU", 'R' }, { "AGU", 'S' }, { "GGU", 'G' },
			{ "UGC", 'C' }, { "CGC", 'R' }, { "AGC", 'S' }, { "GGC", 'G' },
			{ "UGA",  0  }, { "CGA", 'R' }, { "AGA", 'R' }, { "GGA", 'G' },
			{ "UGG", 'W' }, { "CGG", 'R' }, { "AGG", 'R' }, { "GGG", 'G' }
		};

		// TODO
	}
}

namespace std
{
	inline auto operator>>(istream &stream, bio::FASTA &arg) -> istream &
	{
		arg.Read(stream);
		return stream;
	}

	inline auto operator<<(ostream &stream, bio::FASTA &arg) -> ostream &
	{
		// TODO
		return stream;
	}
}

#endif