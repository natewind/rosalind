// Computing GC Content

#include <string>

#include "../common/io.hpp"
#include "../common/biolib.hpp"

auto main() -> int
{
	using namespace bio;

	auto max_id = std::string();
	auto max_gc = float(0);

	for (FASTA record : utils::open("rosalind_gc.txt"))
	{
		auto const gc = DNA(record).ContentGC();

		if (gc > max_gc)
		{
			max_gc = gc;
			max_id = record.Id();
		}
	}

	auto result = utils::open("result.txt", utils::write);
	result.print(max_id);
	result.print(pct(max_gc));
}
