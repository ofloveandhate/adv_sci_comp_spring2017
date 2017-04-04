// this code is provided specifically to demonstrate a data race
// in openmp.

// can you spy the data race?

#include <omp.h>

#include <vector>
#include <iostream>

int main()
{
	int counter = 0;

	constexpr auto size = 1000;
	std::vector<int> ints(size);
	#pragma omp parallel for
	for (int ii=0; ii<size; ++ii)
	{
		if (ii%2)
			++counter;
	}


	std::cout << counter << '\n';

	return 0;
}
