// Mendel’s First Law

#include "../common/io.hpp"
#include "../common/biolib.hpp"

auto main() -> int
{
	auto data = utils::open("rosalind_iprb.txt");
	auto result = utils::open("result.txt", utils::write);

	// TODO: Make ‘void open::read(tuple)’ function in pythonize?
	auto const k = int(utils::input());
	auto const m = int(utils::input());
	auto const n = int(utils::input());

	auto denom = k + m + n;
	denom *= denom - 1;

	// TODO: Generalize the algorithm and move it to biolib
	auto const num = k * (2 * (m + n) + k - 1) + m * (n + 3 * (m - 1) / 4.0f);
	result.print(num / denom);
}
