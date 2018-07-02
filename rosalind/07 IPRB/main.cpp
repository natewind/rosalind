// Mendel’s First Law

#include <biolib>
#include <pythonized>

int main()
{
	auto data = open("rosalind_iprb.txt");
	auto result = open("result.txt", write);

	// TODO: Make ‘void open::read(tuple)’ function in pythonize?
	int k, m, n;
	k = input();
	k = input();
	n = input();

	int denom = k + m + n;
	denom *= denom - 1;

	// TODO: Generalize the algorithm and move it to biolib
	float num = k * (2 * (m + n) + k - 1) + m * (n + 3 * (m - 1) / 4.0);
	result.print(num / denom);
}
