// Counting DNA Nucleotides

#include "../common/io.hpp"
#include "../common/biolib.hpp"

auto main() -> int
{
	auto data = utils::open("rosalind_dna.txt");
	auto result = utils::open("result.txt", utils::write);

	bio::DNA const dna = data.input();
	auto const [A, C, G, T] = dna.Count();
	result.print(A, C, G, T);
}
