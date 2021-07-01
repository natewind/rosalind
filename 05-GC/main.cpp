// Computing GC Content

#include <string>  // std::string
#include <utility> // std::move

#include "../common/file.hpp"
#include "../common/biolib.hpp"

struct MaxGC
{
	std::string id;
	bio::Percent gc = 0;

	void update(bio::FASTA record)
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
	auto max = MaxGC();

	for (bio::FASTA record : open("rosalind_gc.txt"))
		max.update(std::move(record));

	auto result = open("result.txt");
	result.print(max.id);
	result.print(max.gc);
}
