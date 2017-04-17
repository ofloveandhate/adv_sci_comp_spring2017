// a toy program demonstrating open mp sections
// for concurrent execution of multiple blobs of code
//
// spring 2017

// consider setting export OMP_NESTED=true
// or the equivalent for your shell of choice


#include <omp.h>
#include <chrono>
#include <iostream>

template <typename DurationT>
void WaitFor(DurationT const& t)
{
	auto start_time = std::chrono::system_clock::now();
	while (std::chrono::system_clock::now()-start_time<t)
	  ; // empty loop statement to do nothing.
	std::cout << t.count() << std::endl;
}



void foo()
{
	WaitFor(std::chrono::seconds(3));
}



void bar()
{
	WaitFor(std::chrono::seconds(4));
}


void dib()
{
	WaitFor(std::chrono::seconds(5));
}

void gaz()
{
	#pragma omp parallel
	#pragma omp sections
	{
		#pragma omp section 
			foo();
		#pragma omp section 
			bar();
	}
}

void zim()
{
	#pragma omp parallel num_threads(2)
	#pragma omp sections
	{
		#pragma omp section 
			foo();
		#pragma omp section 
			bar();
	}
}

void gir()
{
	#pragma omp parallel num_threads(2)
	#pragma omp sections
	{
		#pragma omp section 
			gaz();
		#pragma omp section 
			zim();
	}
}

int main()
{
	auto start_time = std::chrono::system_clock::now();

	gir();

	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now()-start_time).count() << " microseconds\n";
}
