#include <iostream>

#include "../basics/timer.hpp"
#include "matrix.hpp"

using namespace advscicomp;


template<typename T>
Matrix<T> MultiplyACC(Matrix<T> A, Matrix<T> B, int M, int N, int P)
{

	auto res = MakeMatrix<T>(M,P);

#pragma acc kernels copyin(A[0:M*N]) copyin(B[0:N*P]) copy(res[0:M*P])
{
	#pragma acc for independent
	for (unsigned ii{0}; ii<M; ++ii)
		#pragma acc for independent
		for (unsigned jj{0}; jj<P; ++jj)
		{
			T t=0;
			#pragma acc for reduction(+:t)
			for (unsigned kk{0}; kk<N; ++kk)
				t += A[ii*M+kk]*B[kk*N+jj];
			res[ii*M+jj] += t;
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

	Matrix<double> C;

	{
		Timer t;
		C = MultiplyACC(A,B, N,N,N);
	}

	auto C_tilde = mul(A,B,N,N,N);
	auto diff = sub(C_tilde, C, N,N);

	if (NormInf(diff,N,N) > tol)
		std::cout << "fail\n";

	ClearMatrix(A);
	ClearMatrix(B);
	ClearMatrix(C);
	ClearMatrix(C_tilde);
	ClearMatrix(diff);

}


int main()
{
	
	
	testmul();


	return 0;
}


