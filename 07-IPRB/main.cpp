// Mendel’s First Law

#include "../cleario/include.hpp"
#include "../common/file.hpp"
#include "../common/biolib.hpp"

auto main() -> int
{
	auto const [RR, Rr, rr] = clear::open("rosalind_iprb.txt").read<int, int, int>();

	auto const population = RR + Rr + rr;
	auto const total_pairings = bio::binomial2(population);

	auto const rr_rr = bio::binomial2(rr);
	auto const Rr_Rr = bio::binomial2(Rr);
	auto const Rr_rr = Rr * rr;

	auto const recessive_offsprings = rr_rr + 0.25f * Rr_Rr + 0.5f * Rr_rr;
	auto const p_dominant = 1 - recessive_offsprings / total_pairings;

	open("result.txt").print(p_dominant);
}
