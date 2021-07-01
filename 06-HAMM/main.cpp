// Counting Point Mutations

#include "../common/file.hpp"
#include "../common/biolib.hpp"

auto main() -> int
{
	auto const [s, t] = open("rosalind_hamm.txt").read<bio::DNA, bio::DNA>();
	open("result.txt").print(distance(s, t));
}
