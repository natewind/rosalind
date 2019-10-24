// Computing GC Content

#include <biolib>
#include <pythonize>

auto main() -> int
{
	using namespace bio;

	str max_id;
	float max_gc = 0;

	for (FASTA record : open("rosalind_gc.txt"))
	{
		auto gc = DNA(record).ContentGC();

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
