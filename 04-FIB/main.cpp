// Rabbits and Recurrence Relations

#include "../common/io.hpp"
#include "../common/biolib.hpp"

auto main() -> int
{
	auto data = utils::open("rosalind_fib.txt");
	auto result = utils::open("result.txt", utils::write);

	auto const n = int(data.input());
	auto const k = int(data.input());
	result.print(bio::fibonacci(n, k));
}
