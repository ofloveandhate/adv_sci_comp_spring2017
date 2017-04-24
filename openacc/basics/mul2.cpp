#include <iostream>

#include "timer.hpp"
#include "matrix.hpp"

using namespace advscicomp;

// parallelized???
// std::__1::array<std::__1::array<T4, T3>, T1> MultiplyACC<(unsigned long)5, (unsigned long)5, (unsigned long)5, double>(const std::__1::array<std::__1::array<T4, T2>, T1> &, const std::__1::array<std::__1::array<T4, T3>, T2> &):
//      18, Loop is parallelizable
//          Generating Multicore code
//          18, #pragma acc loop gang
//      19, Loop is parallelizable
//      20, Complex loop carried dependence of  prevents parallelization


template<SizeT M, SizeT N, SizeT P, typename T>
Matrix<M,P,T> MultiplyACC(Matrix<M,N,T> const& A, Matrix<N,P,T> const& B)
{

	auto res = Matrix<M,P,T>{};

#pragma acc kernels
{
	#pragma acc for independent
	for (unsigned ii{0}; ii<M; ++ii)
		#pragma acc for independent
		for (unsigned jj{0}; jj<P; ++jj)
		{
			T t=0;
			#pragma acc for reduction(+:t)
			for (unsigned kk{0}; kk<N; ++kk)
				t += A[ii][kk]*B[kk][jj];
			res[ii][jj] += t;
		}
} // kernels

	return res;
}



void testmul()
{
	double tol = 1e-7;

	constexpr int N = 100;

	auto A = RandomMat<N,N,double>();
	auto B = RandomMat<N,N,double>();

	auto C = MultiplyACC(A,B);

	auto C_tilde = A*B;


	if (NormInf(C_tilde - C) > tol)
		std::cout << "fail\n";
}


int main()
{
	Timer t;
	
	testmul();


	return 0;
}


