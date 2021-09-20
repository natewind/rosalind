// Transcribing DNA into RNA

#include "../cleario/main.hpp"
#include "../common/file.hpp"
#include "../common/biolib.hpp"

#include <utility> // std::move

auto main() -> int
{
	auto dna = open("rosalind_rna.txt").read<bio::DNA>();
	auto const rna = transcribe(std::move(dna));
	clear::open("result.txt").print(rna);
}
