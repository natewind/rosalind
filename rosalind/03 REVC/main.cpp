// Complementing a Strand of DNA

#include <biolib>
#include <pythonize>

auto main() -> int
{
	auto data = open("rosalind_revc.txt");
	auto result = open("result.txt", write);
	bio::DNA strand = data.input();
	result.print(strand.Complement());
}
