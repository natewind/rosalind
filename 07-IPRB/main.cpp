// Mendel’s First Law

#include "../common/file.hpp"
#include "../common/biolib.hpp"

// auto main() -> int
// {
// 	auto const [k, m, n] = open("rosalind_iprb.txt").read<int, int, int>();

// 	auto denom = k + m + n;
// 	denom *= denom - 1;

// 	// TODO: Generalize the algorithm and move it to biolib
// 	auto const num = k * (2 * (m + n) + k - 1) + m * (n + 3 * (m - 1) / 4.0f);
// 	open("result.txt").print(num / denom);
// }

auto main() -> int
{
	auto const [RR, Rr, rr] = open("rosalind_iprb.txt").read<int, int, int>();

	auto const total = RR + Rr + rr;
	// auto const total_outcomes = total * (total - 1) / 2;

	// auto const pure_recessive = rr * (rr - 1) / 2;
	// auto const pure_heterozygous = Rr * (Rr - 1) / 2;
	// auto const recessive_heterozygous = Rr * rr;

	// ATTEMPT 1

	// auto const recessive_outcomes = pure_recessive
	//                               + 0.25 * double(pure_heterozygous)
	//                               + 0.50 * double(recessive_heterozygous);

	// auto const p_dominant = 1 - recessive_outcomes / total_outcomes;

	//=========================================================================

	// ATTEMPT 2

	// auto const recessive_outcomes = 4 * pure_recessive
	//                               + pure_heterozygous
	//                               + 2 * recessive_heterozygous;

	// auto const p_dominant = (4.0 * total_outcomes - recessive_outcomes) / (4 * total_outcomes);

	//=========================================================================

	// ATTEMPT 3

	auto const p_dominant =

		(long double)
		(4 * (total * (total - 1) - rr * (rr - 1) - Rr * rr) - Rr * (Rr - 1))
		/
		(4 * total * (total - 1));

	// WHAT THE ACTUAL FUCK

	open("result.txt").print(p_dominant);
}
