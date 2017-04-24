#include <iostream>

#include "../basics/timer.hpp"
#include "matrix.hpp"

using namespace advscicomp;

// parallelized???
// std::__1::array<std::__1::array<T4, T3>, T1> MultiplyACC<(unsigned long)5, (unsigned long)5, (unsigned long)5, double>(const std::__1::array<std::__1::array<T4, T2>, T1> &, const std::__1::array<std::__1::array<T4, T3>, T2> &):
//      18, Loop is parallelizable
//          Generating Multicore code
//          18, #pragma acc loop gang
//      19, Loop is parallelizable
//      20, Complex loop carried dependence of  prevents parallelization


template<typename T>
Matrix<T> MultiplyACC(Matrix<T> const& A, Matrix<T> const& B, int M, int N, int P)
{

	auto res = MakeMatrix<T>(M,P);

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

	constexpr int N = 1000;

	auto A = RandomMat<double>(N,N);
	auto B = RandomMat<double>(N,N);

	auto C = MultiplyACC(A,B, N,N,N);

	auto C_tilde = mul(A,B,N,N,N);
	auto diff = sub(C_tilde, C, N,N);

	if (NormInf(diff,N,N) > tol)
		std::cout << "fail\n";

	ClearMatrix(A,N,N);
	ClearMatrix(B,N,N);
	ClearMatrix(C,N,N);
	ClearMatrix(C_tilde,N,N);
	ClearMatrix(diff,N,N);

}


int main()
{
	Timer t;
	
	testmul();


	return 0;
}


