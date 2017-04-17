// a toy program demonstrating open mp sections
// for concurrent execution of multiple blobs of code
//
// spring 2017

#include <omp.h>
#include <chrono>
#include <iostream>

/**
there's also 
std::this_thread::sleep_for(std::chrono::seconds(1));
*/
template <typename DurationT>
void WaitFor(DurationT const& t)
{
	auto start_time = std::chrono::system_clock::now();
	while (std::chrono::system_clock::now()-start_time<t)
	  ; // empty loop statement to do nothing.
}



void foo()
{
	WaitFor(std::chrono::seconds(3));
}



void bar()
{
	WaitFor(std::chrono::seconds(4));
}



int main()
{
	auto start_time = std::chrono::system_clock::now();
#pragma omp parallel
	#pragma omp sections
	{
		#pragma omp section 
			foo();
		#pragma omp section 
			bar();
	}

	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now()-start_time).count() << " microseconds\n";
}
