// Transcribing DNA into RNA

#include "../common/file.hpp"
#include "../common/biolib.hpp"

auto main() -> int
{
	auto const dna = open("rosalind_rna.txt").read<bio::DNA>();
	open("result.txt").print(transcribe(dna));
}
