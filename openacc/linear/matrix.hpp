// a c-style matrix header "library"



#pragma once

#include "../basics/random.hpp"


namespace advscicomp{


template<typename T = double>
using Matrix = T*;

template<typename T = double>
using Vector = T*;

template<typename T = double>
Matrix<T> MakeMatrix(int M, int N)
{
	return new T[M*N];
}

template<typename T = double>
Vector<T> MakeVector(int N)
{
	return new int[N];
}

template<typename T>
void ClearMatrix(Matrix<T> m)
{
	delete[] m;
}

template<typename T>
void ClearVector(Vector<T> v)
{
	delete[] v;
}


template<typename T>
Matrix<T> mul(Matrix<T> const& A, Matrix<T> const& B, int M, int N, int P)
{
	auto res = MakeMatrix<T>(M,P);

	for (unsigned ii{0}; ii<M; ++ii)
		for (unsigned jj{0}; jj<P; ++jj)
			for (unsigned kk{0}; kk<N; ++kk)
				res[ii*M+jj] += A[ii*M+kk]*B[kk*N+jj];

	return res;
}


template<typename T>
Matrix<T> sub(Matrix<T> const& A, Matrix<T> const& B, int M, int N)
{
	auto res = MakeMatrix<T>(M,N);
	for (unsigned ii{0}; ii<M; ++ii)
		for (unsigned jj{0}; jj<N; ++jj)
			res[ii*M+jj] =  A[ii*M+jj] - B[ii*N+jj];

	return res;
}

template<typename T>
T NormInf(Matrix<T> const& A, int M, int N)
{
	using std::abs;
	T m{0};
	for (int ii=0; ii<M; ++ii)
		for (int jj=0; jj<N; ++jj)
			if (abs(A[ii*M+jj]) > m)
				m = A[ii*M+jj];

	return m;
}


template<typename T = double>
Vector<T> RandomVec(int N)
{
	auto v = MakeVector<T>(N);
	for (int ii{0}; ii<N; ++ii)
		v[ii] = Random<T>::Generate();
	return v;
}

template<typename T = double>
Matrix<T> RandomMat(int M, int N)
{
	auto A = MakeMatrix<T>(M,N);
	for (int ii{0}; ii<M; ++ii)
		for (int jj{0}; jj<N; ++jj)
			A[ii*M+jj] = Random<T>::Generate();
	return A;
}


} // advscicomp

