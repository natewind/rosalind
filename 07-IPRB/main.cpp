// Mendel’s First Law

#include "../common/io.hpp"
#include "../common/biolib.hpp"

auto main() -> int
{
	auto const [k, m, n] = open("rosalind_iprb.txt").read<int, int, int>();

	auto denom = k + m + n;
	denom *= denom - 1;

	// TODO: Generalize the algorithm and move it to biolib
	auto const num = k * (2 * (m + n) + k - 1) + m * (n + 3 * (m - 1) / 4.0f);
	open("result.txt").print(num / denom);
}
