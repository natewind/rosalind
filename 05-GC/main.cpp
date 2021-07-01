// Computing GC Content

#include <string>  // std::string
#include <utility> // std::move

#include "../common/file.hpp"
#include "../common/biolib.hpp"

struct RecordGC
{
	std::string id;
	bio::Percent gc;

	void update_max(bio::FASTA record)
	{
		auto const new_gc = gc_content(record.get_dna());

		if (new_gc > gc)
		{
			gc = new_gc;
			id = record.id;
		}
	}
};

auto main() -> int
{
	auto max = RecordGC {{}, 0};

	for (bio::FASTA record : open("rosalind_gc.txt"))
		max.update_max(std::move(record));

	auto result = open("result.txt");
	result.print(max.id);
	result.print(max.gc);
}
