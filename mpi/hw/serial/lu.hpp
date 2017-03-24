// lu decomposition code



#pragma once


#include "random.hpp"
#include "matrix.hpp"
#include <tuple>

namespace advscicomp{





template<SizeT N, typename T>
std::tuple<Matrix<N,N,T>, Matrix<N,N,T>> LU(Matrix<N,N,T> const& A)
{
	Matrix<N,N,T> L{}, U{};

	for (unsigned ii{0}; ii<N; ++ii)
	{
		for (unsigned jj{ii}; jj<N; ++jj)
		{
			U[ii][jj] = A[ii][jj];
			for (unsigned kk{0}; kk<ii; kk++)
				U[ii][jj] -= L[ii][kk]*U[kk][jj];
		}

		for (unsigned jj{ii+1}; jj<N; ++jj)
		{
			L[jj][ii] = A[jj][ii];
			for (unsigned kk{0}; kk<ii; kk++)
				L[jj][ii] -= L[jj][kk]*U[kk][ii];
			L[jj][ii] = L[jj][ii] / U[ii][ii];
		}
		
	}

	for (unsigned ii{0}; ii<N; ++ii)
		L[ii][ii] = T{1};

	return std::make_tuple(L,U);
}


template<SizeT N, typename T>
void LU_InPlace(Matrix<N,N,T> & A)
{
	for (unsigned k{0}; k<N; ++k) // for every row
	{
		// first do the U part
		for (unsigned m{k}; m<N; ++m) // for every column to the right, starting at the diagonal entry in row k
			for (unsigned j{0}; j<k; ++j)  // for each row above
				A[k][m] -= A[k][j]*A[j][m];  // do a gaussian row elimination from row j above
		
		// then the L part
		// these numbers essentially record the steps necessary to UNDO the gaussian elimination we just did
		for (unsigned i{k+1}; i<N; ++i) // for each row strictly below the current
		{
			// this loop takes subtracts from the lower entry, 
			// the outer product of the subvector to the left of this lower entry (Aik), 
			// and the subvector above the diagonal entry.
			for (unsigned j{0}; j<k; ++j) // for each column to the right, including this, up to but not incl the diagonal
				A[i][k] -= A[i][j]*A[j][k];
			
			// then, we finish by dividing by the diagonal element
			A[i][k] /= A[k][k]; // divide by the kth diagonal element
		}
	}
}


template<SizeT N, typename T>
void LU_Col_InPlace(Matrix<N,N,T> & A)
{
	for (unsigned k{0}; k<N; ++k) // for every column
	{
		// first do the L part
		// then, we finish by dividing by the diagonal element
		for (unsigned i{k+1}; i<N; ++i) // for each row strictly below the diagonal in the current col
			A[i][k] /= A[k][k]; // divide by the kth diagonal element


		for (unsigned j{k+1}; j<N; ++j) 
			for (unsigned i{k+1}; i<N; ++i)  
				A[i][j] -= A[i][k]*A[k][j];  // do a gaussian row elimination from row j above
	}
}

template<SizeT N, typename T>
std::tuple<Matrix<N,N,T>, Matrix<N,N,T>> UnpackToLU(Matrix<N,N,T> const& lu_result)
{
	Matrix<N,N,T> L{};
	Matrix<N,N,T> U{};

	for (unsigned ii{0}; ii<N; ++ii)
		for (unsigned jj{ii}; jj<N; ++jj)
			U[ii][jj] = lu_result[ii][jj];

	for (unsigned ii{0}; ii<N; ++ii)
		for (unsigned jj{0}; jj<ii; ++jj)
			L[ii][jj] = lu_result[ii][jj];

	for (unsigned ii{0}; ii<N; ++ii)
		L[ii][ii] = T{1};

	return std::make_tuple(L,U);
}



} // namespace

