// Mendel’s First Law

#include "../common/file.hpp"
#include "../common/biolib.hpp"

auto main() -> int
{
	auto const [n_dominant, n_heterozygous, n_recessive] = open("rosalind_iprb.txt").read<int, int, int>();

	auto denom = n_dominant + n_heterozygous + n_recessive;
	denom *= denom - 1;

	// TODO: Generalize the algorithm and move it to biolib
	auto const num = n_dominant * (2 * (n_heterozygous + n_recessive) + n_dominant - 1) + n_heterozygous * (n_recessive + 3 * (n_heterozygous - 1) / 4.0f);
	open("result.txt").print(num / denom);
}

// auto main() -> int
// {
// 	auto const [k_AA, m_Aa, n_aa] = open("rosalind_iprb.txt").read<int, int, int>();

// 	auto denom = k_AA + m_Aa + n_aa;
// 	denom *= denom - 1;

// 	// TODO: Generalize the algorithm and move it to biolib
// 	auto const num = k_AA * (2 * (m_Aa + n_aa) + k_AA - 1) + m_Aa * (n_aa + 3 * (m_Aa - 1) / 4.0f);
// 	open("result.txt").print(num / denom);
// }
