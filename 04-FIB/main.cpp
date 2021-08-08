// Rabbits and Recurrence Relations

#include "../common/file.hpp"
#include "../common/biolib.hpp"

auto main() -> int
{
	auto const [months, pairs] = open("rosalind_fib.txt").read<int, int>();
	open("result.txt").print(bio::LucasSequence{1, -pairs}[months]);
}
