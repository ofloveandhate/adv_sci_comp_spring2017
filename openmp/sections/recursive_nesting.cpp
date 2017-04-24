#include <omp.h>
#include <chrono>
#include <iostream>

template <typename DurationT>
void WaitFor(DurationT const& t)
{
	auto start_time = std::chrono::system_clock::now();
	while (std::chrono::system_clock::now()-start_time<t)
	  ; // empty loop statement to do nothing.
}


void foo(int i, int max_depth)
{
#pragma omp parallel num_threads(2)
	{
		if (i < max_depth)
			foo(i+1, max_depth);
		else
			WaitFor(std::chrono::milliseconds(10));;
	}
}


int main()
{

#pragma omp parallel num_threads(2)
	foo(0, 9);

return 0;
}


