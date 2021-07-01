// Complementing a Strand of DNA

#include "../common/io.hpp"
#include "../common/biolib.hpp"

auto main() -> int
{
	auto const dna = open("rosalind_revc.txt").read<bio::DNA>();
	open("result.txt", write).print(dna.Complement());
}
