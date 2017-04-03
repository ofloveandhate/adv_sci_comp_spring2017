// a basic program for computing the inner product of two vectors, 
// in parallel using OpenMP

#include <omp.h>


#include "../../mpi/hw/serial/random.hpp"
#include "../../mpi/hw/serial/matrix.hpp"
#include <iostream>

namespace advscicomp{

template<SizeT N, typename T>
T Dot(Vector<N,T> const& v, Vector<N,T> const& w)
{
	T result{0};

	#pragma omp parallel
	{ // start parallel region

		T my_result{0};
		#pragma omp for
		for (int ii = 0; ii<N; ++ii)
		{
			my_result += v[ii] * w[ii];
		}
		// now my_result contains a partial result. 
		#pragma omp atomic
		result += my_result;
	} // end parallel region

	return result;
}

}



namespace test
{
using namespace advscicomp;
void InnerProduct()
{
	constexpr SizeT tested_size = 10000;

	auto a = Vector<tested_size>{};
	auto b = Vector<tested_size>{};
	for (int ii=0; ii<tested_size; ++ii)
	{
		a[ii] = 1;
		b[ii] = 1;
	}

	auto d = Dot(a,b);
	using std::abs;
	if (abs(d-tested_size) >= 1e-7)
		std::cout << "fail in InnerProduct\n";
}


void RunSuite()
{
	#pragma omp parallel
		#pragma omp single
			std::cout << "running test suite on " << omp_get_num_threads() << " threads\n\n";

	InnerProduct();

	std::cout << "all tests passed\n\n";
}


}

int main(int argc, char** argv)
{
	using namespace advscicomp;

	constexpr SizeT tested_size = 10000;

	

	const auto a = RandomVec<tested_size>();
	const auto b = RandomVec<tested_size>();

	test::RunSuite();

	return 0;
}