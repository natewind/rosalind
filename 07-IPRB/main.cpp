// Mendel’s First Law

#include <pythonize>
#include "../common/biolib.hpp"

auto main() -> int
{
	auto data = open("rosalind_iprb.txt");
	auto result = open("result.txt", write);

	// TODO: Make ‘void open::read(tuple)’ function in pythonize?
	auto const k = int(input());
	auto const m = int(input());
	auto const n = int(input());

	auto denom = k + m + n;
	denom *= denom - 1;

	// TODO: Generalize the algorithm and move it to biolib
	auto const num = k * (2 * (m + n) + k - 1) + m * (n + 3 * (m - 1) / 4.0f);
	result.print(num / denom);
}
