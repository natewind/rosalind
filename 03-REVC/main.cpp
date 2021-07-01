// Complementing a Strand of DNA

#include "../common/file.hpp"
#include "../common/biolib.hpp"

auto main() -> int
{
	auto const dna = open("rosalind_revc.txt").read<bio::DNA>();
	open("result.txt").print(reverse_complement(dna));
}
