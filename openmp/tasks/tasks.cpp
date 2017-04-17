// a simple demonstration of using the tasks from
// OpenMP, version 3 on
//
// spring 2017

#include <omp.h>

#include <iostream>


int foo();

int bar();


int main()
{
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
	return 0;
}


int foo()
{
	return 1;
}



int bar()
{
	return 1;
}

