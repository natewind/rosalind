// Counting DNA Nucleotides

#include <biolib>
#include <pythonize>

auto main() -> int
{
	auto data = open("rosalind_dna.txt");
	auto result = open("result.txt", write);

	bio::DNA const dna = data.input();
	auto const [A, C, G, T] = dna.Count();
	result.print(A, C, G, T);
}
