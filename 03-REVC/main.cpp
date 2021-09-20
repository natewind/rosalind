// Complementing a Strand of DNA

#include "../cleario/main.hpp"
#include "../common/file.hpp"
#include "../common/biolib.hpp"

auto main() -> int
{
	auto const dna = open("rosalind_revc.txt").read<bio::DNA>();
	clear::open("result.txt").print(reverse_complement(dna));
}
