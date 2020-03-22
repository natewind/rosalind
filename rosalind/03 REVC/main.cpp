// Complementing a Strand of DNA

#include <biolib>
#include <pythonize>

auto main() -> int
{
	auto data = open("rosalind_revc.txt");
	auto result = open("result.txt", write);

	bio::DNA const dna = data.input();
	result.print(dna.Complement());
}
