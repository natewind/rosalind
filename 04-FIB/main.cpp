// Rabbits and Recurrence Relations

#include "../common/io.hpp"
#include "../common/biolib.hpp"

auto main() -> int
{
	auto const [n, k] = open("rosalind_fib.txt").read<int, int>();
	open("result.txt", write).print(bio::fibonacci(n, k));
}
