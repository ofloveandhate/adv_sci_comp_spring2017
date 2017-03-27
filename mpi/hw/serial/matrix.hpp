// a little bit of code defining matrices.


#pragma once

#include "random.hpp"
#include <array>

namespace advscicomp{




using SizeT = unsigned long;

template<SizeT M, SizeT N, typename T = double>
using Matrix =  std::array<std::array<T, N>, M>;

template<SizeT M, SizeT N, typename T = double>
using MatrixColMaj =  std::array<std::array<T, M>, N>;

template<SizeT N, typename T = double>
using Vector = std::array<T, N>;




template<SizeT M, SizeT N, SizeT P, typename T>
Matrix<M,P,T> operator*(Matrix<M,N,T> const& A, Matrix<N,P,T> const& B)
{
	auto res = Matrix<M,P,T>{};

	for (unsigned ii{0}; ii<M; ++ii)
		for (unsigned jj{0}; jj<P; ++jj)
			for (unsigned kk{0}; kk<N; ++kk)
				res[ii][jj] += A[ii][kk]*B[kk][jj];

	return res;
}




template<SizeT M, SizeT N, typename T>
std::ostream& operator<<(std::ostream & out, Matrix<M,N,T> const& A)
{
	static constexpr auto pad = 5;
	auto p = out.precision() + pad;
	out << "[...\n";
	for (const auto& x : A)
	{
		out << "[";
		for (const auto& y : x)
			out << std::setw(p) << y << " ";
		out << "];...\n";
	}
	out << "];\n";
	return out;
}




template<SizeT N, typename T = double>
Matrix<N,N,T> Identity()
{
	auto A = Matrix<N,N,T>{};
	for (SizeT ii{0}; ii<N; ++ii)
		A[ii][ii] = T{1};
	return A;
}


template<SizeT M, SizeT N = M, typename T = double>
Matrix<M,N,T> RandomMat()
{
	auto A = Matrix<M,N,T>{};
	for (SizeT ii{0}; ii<M; ++ii)
		for (SizeT jj{0}; jj<N; ++jj)
			A[ii][jj] = Random<T>::Generate();
	return A;
}



}// namespace

