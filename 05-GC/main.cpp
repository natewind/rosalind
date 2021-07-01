// Computing GC Content

#include <string> // std::string

#include "../common/file.hpp"
#include "../common/biolib.hpp"

struct RecordGC
{
	std::string id;
	bio::Percent gc;
};

auto main() -> int
{
	auto max = RecordGC {{}, 0};

	for (bio::FASTA record : open("rosalind_gc.txt"))
	{
		auto const gc = gc_content(record.get_dna());

		if (gc > max.gc)
		{
			max.gc = gc;
			max.id = record.id;
		}
	}

	auto result = open("result.txt");
	result.print(max.id);
	result.print(max.gc);
}
