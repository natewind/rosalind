// Transcribing DNA into RNA

#include <utility> // std::move

#include "../common/file.hpp"
#include "../common/biolib.hpp"

auto main() -> int
{
	auto dna = open("rosalind_rna.txt").read<bio::DNA>();
	auto const rna = transcribe(std::move(dna));
	open("result.txt").print(rna);
}
