// Mendel’s First Law

#include "../common/file.hpp"
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

// auto main() -> int
// {
// 	auto const [k_AA, m_Aa, n_aa] = open("rosalind_iprb.txt").read<int, int, int>();

// 	auto denom = k_AA + m_Aa + n_aa;
// 	denom *= denom - 1;

// 	// TODO: Generalize the algorithm and move it to biolib
// 	auto const num = k_AA * (2 * (m_Aa + n_aa) + k_AA - 1) + m_Aa * (n_aa + 3 * (m_Aa - 1) / 4.0f);
// 	open("result.txt").print(num / denom);
// }
