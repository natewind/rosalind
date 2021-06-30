// Complementing a Strand of DNA

#include "../common/io.hpp"
#include "../common/biolib.hpp"

auto main() -> int
{
	auto data = utils::open("rosalind_revc.txt");
	auto result = utils::open("result.txt", utils::write);

	bio::DNA const dna = data.input();
	result.print(dna.Complement());
}
