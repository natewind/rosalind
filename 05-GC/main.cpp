// Computing GC Content

#include <string>

#include "../common/file.hpp"
#include "../common/biolib.hpp"

auto main() -> int
{
	auto max_id = std::string();
	auto max_gc = float(0);

	for (bio::FASTA record : open("rosalind_gc.txt"))
	{
		auto const gc = bio::DNA(record).ContentGC();

		if (gc > max_gc)
		{
			max_gc = gc;
			max_id = record.Id();
		}
	}

	auto result = open("result.txt");
	result.print(max_id);
	result.print(pct(max_gc));
}
