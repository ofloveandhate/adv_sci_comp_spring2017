// a simple demonstration of using the tasks from
// OpenMP, version 3 on
//
// spring 2017

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


int foo();

int bar();


int main()
{
	auto start_time = std::chrono::system_clock::now();
	int x, y;
#pragma omp parallel
	#pragma omp single nowait
	{
		#pragma omp task shared(x)
			x = foo();
		#pragma omp task shared(y)
			y = bar();

		#pragma omp taskwait
		x += y;
	}

std::cout << x << std::endl;

std::cout << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now()-start_time).count() << " microseconds\n";
	return 0;
}


int foo()
{
	WaitFor(std::chrono::seconds(1));
	return 1;
}



int bar()
{
	WaitFor(std::chrono::seconds(1));
	return 1;
}

