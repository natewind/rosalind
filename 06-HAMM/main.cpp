// Counting Point Mutations

#include <pythonize>
#include "../common/biolib.hpp"

auto main() -> int
{
	auto data = open("rosalind_hamm.txt");
	auto result = open("result.txt", write);

	bio::DNA const s = data.input();
	bio::DNA const t = data.input();
	result.print(s.Distance(t));
}
