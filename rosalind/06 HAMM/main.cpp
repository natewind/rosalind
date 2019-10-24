// Counting Point Mutations

#include <biolib>
#include <pythonize>

auto main() -> int
{
	auto data = open("rosalind_hamm.txt");
	auto result = open("result.txt", write);

	bio::DNA s = data.input();
	bio::DNA t = data.input();
	result.print(s.Distance(t));
}
