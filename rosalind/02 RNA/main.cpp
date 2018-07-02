// Transcribing DNA into RNA

#include <biolib>
#include <pythonize>

int main()
{
	auto data = open("rosalind_rna.txt");
	auto result = open("result.txt", write);
	bio::DNA strand = data.input();
	result.print(bio::RNA(strand));
}
