#include <iostream>
#include <chrono>
#include "matrix.hpp"

using namespace advscicomp;

class Timer
{
public:
	Timer() : start_time(std::chrono::system_clock::now())
	{ }

	~Timer()
	{
		std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start_time).count() << std::endl;
	}
private:
	std::chrono::time_point<std::chrono::system_clock> start_time;
};

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


int main()
{
	Timer t;
	auto A = RandomMat<5,5,double>();
	auto B = RandomMat<5,5,double>();

	auto C = MultiplyACC(A,B);


	return 0;
}


