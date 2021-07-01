// Rabbits and Recurrence Relations

#include "../common/file.hpp"
#include "../common/biolib.hpp"

auto main() -> int
{
	auto const [n, k] = open("rosalind_fib.txt").read<int, int>();
	open("result.txt").print(bio::LucasSequence(1, -k)[n]);
}
