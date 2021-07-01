// Complementing a Strand of DNA

#include "../common/io.hpp"
#include "../common/biolib.hpp"

// TODO: Move to biolib
auto ReverseComplement(std::string const &dna) -> std::string
{
	auto result = std::string();
	result.reserve(dna.size());

	std::transform
	(
		std::rbegin(dna), std::rend(dna),
		std::back_inserter(result), bio::complement
	);

	return result;
}

auto main() -> int
{
	auto const dna = open("rosalind_revc.txt").read<bio::DNA>();
	open("result.txt").print(ReverseComplement(dna));
}
