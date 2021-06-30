// Counting Point Mutations

#include "../common/io.hpp"
#include "../common/biolib.hpp"

auto main() -> int
{
	auto data = utils::open("rosalind_hamm.txt");
	auto result = utils::open("result.txt", utils::write);

	bio::DNA const s = data.input();
	bio::DNA const t = data.input();
	result.print(s.Distance(t));
}
