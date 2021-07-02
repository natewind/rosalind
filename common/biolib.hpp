#ifndef BIOLIB_HPP
#define BIOLIB_HPP

#include <tuple>         // std::tuple, std::get
#include <string>        // std::string, std::getline
#include <istream>       // std::istream, std::ostream
#include <numeric>       // std::accumulate
#include <iterator>      // std::back_inserter
#include <algorithm>     // std::replace, std::count_if, std::min
#include <functional>    // std::plus, std::not_equal_to
#include <unordered_map> // std::unordered_map

// TODO: Rewrite in Haskell or Rust

namespace bio
{
	using ACGT = std::tuple<int, int, int, int>;

	struct DNA { std::string data; };
	struct RNA { std::string data; };

	struct FASTA
	{
		std::string id;
		std::string sequence;

		auto get_dna() const -> DNA { return {sequence}; }
	};

	struct Percent
	{
		float value;
		constexpr Percent(float x) : value(100 * x) {}

		constexpr auto operator>(Percent other) const
		{
			return value > other.value;
		}
	};

	constexpr auto add_base(ACGT ns, char b) -> ACGT
	{
		switch (b)
		{
			case 'A': ++std::get<0>(ns); break;
			case 'C': ++std::get<1>(ns); break;
			case 'G': ++std::get<2>(ns); break;
			default : ++std::get<3>(ns); break;
		}

		return ns;
	}

	template <class Strand>
	constexpr auto count_bases(Strand const &xs) -> ACGT
	{
		return std::accumulate
		(
			begin(xs.data), end(xs.data),
			ACGT {0, 0, 0, 0}, add_base
		);
	}

	auto transcribe(DNA const &dna) -> RNA
	{
		auto rna = RNA {dna.data};
		std::replace(begin(rna.data), end(rna.data), 'T', 'U');
		return rna;
	}

	constexpr auto complement(char c) -> char
	{
		switch (c)
		{
			case 'A': return 'T';
			case 'C': return 'G';
			case 'G': return 'C';
			default : return 'A';
		}
	}

	auto reverse_complement(DNA const &dna) -> DNA
	{
		auto revc = DNA();
		revc.data.reserve(dna.data.size());

		std::transform
		(
			rbegin(dna.data), rend(dna.data),
			back_inserter(revc.data), complement
		);

		return revc;
	}

	struct LucasSequence
	{
		int p = 1;
		int q = 1;

		constexpr LucasSequence(int p, int q) : p(p), q(q) {}

		constexpr auto at(int n, long a = 0, long b = 1) const -> long
		{
			return (n == 0) ? a
			     : (n == 1) ? b
			     : (n >= 2) ? at(n - 1, b, p * b - q * a)
			                : at(n + 1, (p * a - b) / q, a);
		}

		constexpr auto operator[](int n) const -> long { return at(n); }
	};

	auto gc_content(DNA const &dna) -> Percent
	{
		constexpr auto is_gc = [](auto c) { return (c == 'G') || (c == 'C'); };

		return std::count_if(begin(dna.data), end(dna.data), is_gc)
		     / float(dna.data.size());
	}

	auto hamming_distance(std::string const &xs, std::string const &ys) -> int
	{
		auto const size = std::min(xs.size(), ys.size());

		return std::inner_product
		(
			begin(xs), begin(xs) + size, begin(ys),
			0, std::plus<int>(), std::not_equal_to<int>()
		);
	}

	inline auto const codon_table = std::unordered_map<char const*, char>
	{
		{"UUU", 'F'}, {"CUU", 'L'}, {"AUU", 'I'}, {"GUU", 'V'},
		{"UUC", 'F'}, {"CUC", 'L'}, {"AUC", 'I'}, {"GUC", 'V'},
		{"UUA", 'L'}, {"CUA", 'L'}, {"AUA", 'I'}, {"GUA", 'V'},
		{"UUG", 'L'}, {"CUG", 'L'}, {"AUG", 'M'}, {"GUG", 'V'},
		{"UCU", 'S'}, {"CCU", 'P'}, {"ACU", 'T'}, {"GCU", 'A'},
		{"UCC", 'S'}, {"CCC", 'P'}, {"ACC", 'T'}, {"GCC", 'A'},
		{"UCA", 'S'}, {"CCA", 'P'}, {"ACA", 'T'}, {"GCA", 'A'},
		{"UCG", 'S'}, {"CCG", 'P'}, {"ACG", 'T'}, {"GCG", 'A'},
		{"UAU", 'Y'}, {"CAU", 'H'}, {"AAU", 'N'}, {"GAU", 'D'},
		{"UAC", 'Y'}, {"CAC", 'H'}, {"AAC", 'N'}, {"GAC", 'D'},
		{"UAA",  0 }, {"CAA", 'Q'}, {"AAA", 'K'}, {"GAA", 'E'},
		{"UAG",  0 }, {"CAG", 'Q'}, {"AAG", 'K'}, {"GAG", 'E'},
		{"UGU", 'C'}, {"CGU", 'R'}, {"AGU", 'S'}, {"GGU", 'G'},
		{"UGC", 'C'}, {"CGC", 'R'}, {"AGC", 'S'}, {"GGC", 'G'},
		{"UGA",  0 }, {"CGA", 'R'}, {"AGA", 'R'}, {"GGA", 'G'},
		{"UGG", 'W'}, {"CGG", 'R'}, {"AGG", 'R'}, {"GGG", 'G'}
	};
}

auto operator>>(std::istream &src, bio::DNA &dna) -> std::istream&
{
	return src >> dna.data;
}

auto operator>>(std::istream &src, bio::RNA &rna) -> std::istream&
{
	return src >> rna.data;
}

auto operator<<(std::ostream &dest, bio::DNA const &dna) -> std::ostream&
{
	return dest << dna.data;
}

auto operator<<(std::ostream &dest, bio::RNA const &rna) -> std::ostream&
{
	return dest << rna.data;
}

auto operator>>(std::istream &src, bio::FASTA &fasta) -> std::istream&
{
	src.get();
	getline(src, fasta.id);

	auto line = std::string();

	for (char c; (c = src.peek()) != '>' && c != EOF; fasta.sequence += line)
		getline(src, line);

	return src;
}

auto operator<<(std::ostream &dest, bio::Percent const &pct) -> std::ostream&
{
	return dest << pct.value;
}

#endif
