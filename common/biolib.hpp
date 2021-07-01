#ifndef BIOLIB_HPP
#define BIOLIB_HPP

#include <tuple>         // std::tuple, std::get, std::tie
#include <string>        // std::string, std::getline
#include <istream>       // std::istream, std::ostream
#include <numeric>       // std::accumulate
#include <iterator>      // std::back_inserter
#include <algorithm>     // std::replace
#include <unordered_map> // std::unordered_map
#include "range.hpp"

// TODO: Finish lucas_sequence and 04-FIB
// TODO: std::tie - ???

// TODO: Finish 05-GC
// TODO: Finish 06-HAMM
// TODO: Finish 07-IPRB

// TODO: Rewrite on Haskell or Rust

namespace bio
{
	using ACGT = std::tuple<int, int, int, int>;

	struct DNA { std::string data; };
	struct RNA { std::string data; };

	struct FASTA
	{
		std::string id;
		std::string sequence;
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
			ACGT { 0, 0, 0, 0 }, add_base
		);
	}

	auto transcribe(DNA const &dna) -> RNA
	{
		auto rna = RNA { dna.data };
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

	// constexpr auto lucas_sequence(int n, int p = 1, int q = 1) -> long
	// {
	// 	auto a = long(0);
	// 	auto b = long(1);

	// 	for (auto _ : range(2, n + 1))
	// 	{
	// 		std::tie(a, b) = std::tuple(b, p * a - q * b);
	// 	}

	// 	return (n == 0) ? a : b;
	// }

	// constexpr auto lucas_sequence(int n, int p = 1, int q = 1) -> long
	// {
	// 	long acc[2] = { 0, 1 };

	// 	for (auto const i : range(2, n + 1))
	// 	{
	// 		auto const last = i & 1;
	// 		acc[last] = p * acc[last] - q * acc[1 - last];
	// 	}

	// 	return acc[n & 1];
	// }

	inline auto const codon_table = std::unordered_map<char const*, char>
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

#endif
