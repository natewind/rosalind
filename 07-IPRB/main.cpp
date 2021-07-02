// Mendel’s First Law

#include "../common/file.hpp"
#include "../common/biolib.hpp"

auto main() -> int
{
	auto const [RR, Rr, rr] = open("rosalind_iprb.txt").read<int, int, int>();

	auto const population = RR + Rr + rr;
	auto const total_outcomes = population * (population - 1) / 2;

	auto const rr_rr = rr * (rr - 1) / 2;
	auto const Rr_Rr = Rr * (Rr - 1) / 2;
	auto const Rr_rr = Rr * rr;

	auto const recessive_outcomes = rr_rr + 0.25f * Rr_Rr + 0.5f * Rr_rr;
	auto const p_dominant = 1 - recessive_outcomes / total_outcomes;

	open("result.txt").print(p_dominant);
}
