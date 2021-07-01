// Counting DNA Nucleotides

#include "../common/io.hpp"
#include "../common/biolib.hpp"

auto main() -> int
{
	auto const dna = open("rosalind_dna.txt").read<bio::DNA>();
	auto const [A, C, G, T] = dna.CountBases();

	open("result.txt", write).print(A, C, G, T);
}
