#include <pythonize>
#include "biolib.hpp"

int main() // Testing
{
	bio::DNA dna;
	std::cin >> dna;
	auto [A, C, G, T] = dna.Count();
	print(A, C, G, T);
}
