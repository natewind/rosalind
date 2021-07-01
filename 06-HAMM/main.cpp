// Counting Point Mutations

#include "../common/io.hpp"
#include "../common/biolib.hpp"

auto main() -> int
{
	auto const [s, t] = open("rosalind_hamm.txt").read<bio::DNA, bio::DNA>();
	open("result.txt", write).print(s.Distance(t));
}
