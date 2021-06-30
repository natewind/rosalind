// Computing GC Content

#include <pythonize>
#include "../common/biolib.hpp"

auto main() -> int
{
	using namespace bio;

	auto max_id = str();
	auto max_gc = float(0);

	for (FASTA record : open("rosalind_gc.txt"))
	{
		auto const gc = DNA(record).ContentGC();

		if (gc > max_gc)
		{
			max_gc = gc;
			max_id = record.Id();
		}
	}

	auto result = open("result.txt", write);
	result.print(max_id);
	result.print(pct(max_gc));
}