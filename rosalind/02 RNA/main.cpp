// Transcribing DNA into RNA

#include <biolib>
#include <pythonize>

auto main() -> int
{
	auto data = open("rosalind_rna.txt");
	auto result = open("result.txt", write);

	bio::DNA const dna = data.input();
	result.print(bio::RNA(dna));
}
