// Rabbits and Recurrence Relations

#include <biolib>
#include <pythonize>

auto main() -> int
{
	auto data = open("rosalind_fib.txt");
	auto result = open("result.txt", write);

	auto n = int(data.input());
	auto k = int(data.input());
	result.print(bio::fibonacci(n, k));
}
