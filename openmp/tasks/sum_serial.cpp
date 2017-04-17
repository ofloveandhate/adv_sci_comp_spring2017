// inspired by and derived from the CC-SA code at 
// https://en.wikibooks.org/wiki/OpenMP/Tasks
//
// spring 2017

#include <omp.h>
#include <iostream>
#include <chrono>


double* alloc_and_populate(size_t size);
void dealloc(double *);
double sum(const double *, size_t);





int main()
{
	auto start_time = std::chrono::system_clock::now();

	const size_t size = 10;
	double *data = alloc_and_populate(size);

	auto S = sum(data, size);


	dealloc(data);
	std::cout << size << " * 0.1 = " << S << " ?\n\n";
	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now()-start_time).count() << " microseconds\n";

	return 0;
}





double sum(const double *a, size_t n)
{
	if (n == 0)
		return 0;
	else if (n==1)
		return *a;
	else
	{	
		auto pos = n/2;
		return sum(a, pos) + sum(a+pos, n-pos);
	}
	
}




double* alloc_and_populate(size_t size)
{
	double *a = new double[size];
	for (size_t ii=0; ii<size; ii++)
	{
		a[ii] = 0.1;
	}
	return a;
}

void dealloc(double *a)
{
	delete[] a;
}