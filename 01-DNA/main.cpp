// Counting DNA Nucleotides

#include "../common/file.hpp"
#include "../common/biolib.hpp"

auto main() -> int
{
	auto const dna = open("rosalind_dna.txt").read<bio::DNA>();
	auto const [A, C, G, T] = count_bases(dna);

	open("result.txt").print(A, C, G, T);
}
