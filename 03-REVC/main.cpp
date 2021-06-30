// Complementing a Strand of DNA

#include <pythonize>
#include "../common/biolib.hpp"

auto main() -> int
{
	auto data = open("rosalind_revc.txt");
	auto result = open("result.txt", write);

	bio::DNA const dna = data.input();
	result.print(dna.Complement());
}
