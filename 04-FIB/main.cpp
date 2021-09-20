// Rabbits and Recurrence Relations

#include "../cleario/main.hpp"
#include "../common/file.hpp"
#include "../common/biolib.hpp"

auto main() -> int
{
	auto const [months, pairs] = open("rosalind_fib.txt").read<int, int>();
	clear::open("result.txt").print(bio::LucasSequence{1, -pairs}[months]);
}
