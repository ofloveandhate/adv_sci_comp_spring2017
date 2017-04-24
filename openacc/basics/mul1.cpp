#include <iostream>

#include "timer.hpp"
#include "matrix.hpp"

using namespace advscicomp;

// in PGI 16.10, yields these notes:
//std::__1::array<std::__1::array<T4, T3>, T1> MultiplyACC<(unsigned long)5, (unsigned long)5, (unsigned long)5, double>(const std::__1::array<std::__1::array<T4, T2>, T1> &, const std::__1::array<std::__1::array<T4, T3>, T2> &):
     // 18, Complex loop carried dependence of  prevents parallelization
     // 19, Complex loop carried dependence of  prevents parallelization
     // 20, Complex loop carried dependence of  prevents parallelization

template<SizeT M, SizeT N, SizeT P, typename T>
Matrix<M,P,T> MultiplyACC(Matrix<M,N,T> const& A, Matrix<N,P,T> const& B)
{

	auto res = Matrix<M,P,T>{};
#pragma acc kernels
{

	for (unsigned ii{0}; ii<M; ++ii)
		for (unsigned jj{0}; jj<P; ++jj)
			for (unsigned kk{0}; kk<N; ++kk)
				res[ii][jj] += A[ii][kk]*B[kk][jj];
} // kernels

	return res;
}


void testmul()
{
	double tol = 1e-7;

	constexpr int N = 32;

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


