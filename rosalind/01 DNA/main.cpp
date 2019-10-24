// Counting DNA Nucleotides

#include <biolib>
#include <pythonize>

auto main() -> int
{
	auto data = open("rosalind_dna.txt");
	auto result = open("result.txt", write);
	bio::DNA strand = data.input();
	auto [A, C, G, T] = strand.Count();
	result.print(A, C, G, T);
}
