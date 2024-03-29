// Counting DNA Nucleotides

#include "../cleario/include.hpp"
#include "../common/file.hpp"
#include "../common/biolib.hpp"

auto main() -> int
{
	auto const dna = open("rosalind_dna.txt").read<bio::DNA>();
	auto const [A, C, G, T] = count_bases(dna);

	clear::open("result.txt").println(A, ' ', C, ' ', G, ' ', T);
}
