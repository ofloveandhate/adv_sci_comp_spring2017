#include <iostream>

#include "timer.hpp"
#include "matrix.hpp"

using namespace advscicomp;

// parallelized???

template<SizeT M, SizeT N, SizeT P, typename T>
Matrix<M,P,T> MultiplyACC(Matrix<M,N,T> const& A, Matrix<N,P,T> const& B)
{

	auto res = Matrix<M,P,T>{};
#pragma acc kernels
{
	#pragma acc loop independent
	for (unsigned ii{0}; ii<M; ++ii)
		#pragma acc loop independent
		for (unsigned jj{0}; jj<P; ++jj)
			#pragma acc loop independent 
			for (unsigned kk{0}; kk<N; ++kk)
				#pragma acc atomic
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


