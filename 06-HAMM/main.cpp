// Counting Point Mutations

#include "../cleario/include.hpp"
#include "../common/file.hpp"
#include "../common/biolib.hpp"

auto main() -> int
{
	auto const [s, t] = open("rosalind_hamm.txt").read<bio::DNA, bio::DNA>();
	clear::open("result.txt").print(bio::hamming_distance(s.data, t.data));
}
