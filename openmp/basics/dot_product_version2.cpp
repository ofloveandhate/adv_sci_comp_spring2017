// the parallel constructs have been modified in this version,
// to use combined parallel and for pragmas,
// and to use a reduction from openmp

#include <omp.h>


#include "../../mpi/hw/serial/random.hpp"
#include "../../mpi/hw/serial/matrix.hpp"
#include <iostream>

namespace advscicomp{

template<SizeT N, typename T>
T Dot(Vector<N,T> const& v, Vector<N,T> const& w)
{
	T result{0};

	#pragma omp parallel for reduction (+:result)
	for (SizeT ii = 0; ii<N; ++ii)
	{
		result += v[ii] * w[ii];
	}

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
	for (SizeT ii=0; ii<tested_size; ++ii)
	{
		a[ii] = 1;
		b[ii] = 2;
	}

	auto d = Dot(a,b);
	using std::abs;
	if (abs(d-2*tested_size) >= 1e-7)
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

	test::RunSuite();

	return 0;
}