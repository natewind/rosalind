// Complementing a Strand of DNA

#include "../cleario/include.hpp"
#include "../common/file.hpp"
#include "../common/biolib.hpp"

auto main() -> int
{
	auto const dna = open("rosalind_revc.txt").read<bio::DNA>();
	clear::open("result.txt").println(reverse_complement(dna));
}
