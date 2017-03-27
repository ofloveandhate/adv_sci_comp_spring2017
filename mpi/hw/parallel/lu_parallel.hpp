// defines parallel helpers, and parallel LU column algorithm


#pragma once

#include "../serial/matrix.hpp"
#include "parallelism.hpp"

namespace advscicomp{


using ParC = ParallelismConfig;


/**
communicates matrix A from head to everyone else, in block rows
*/
template<SizeT N, typename T>
void DistributeMatrixAllAll(Matrix<N,N,T> & A)
{

	if (ParC::num_procs>1)
		for (unsigned ii{0}; ii<N; ++ii)
			MPI_Bcast(A[ii].data(), N, NumTraits<T>::MPI_Type, ParC::head, MPI_COMM_WORLD);
}



std::tuple<std::vector<unsigned>,std::vector<unsigned>> PartitionOf(SizeT N)
{
	std::vector<unsigned> lower_indices(ParC::num_procs);
	std::vector<unsigned> upper_indices(ParC::num_procs);

	if (ParC::num_procs <= N){
		auto nrows_uniform = N/ParC::num_procs;

		for (unsigned ii{0}; ii<ParC::num_procs; ++ii)
		{
			lower_indices[ii] = ii * nrows_uniform;
			upper_indices[ii] = lower_indices[ii] + nrows_uniform;
		}
		upper_indices[ParC::num_procs-1] = N; // adjust upper index preventing overflow
	}
	else
	{
		for (SizeT ii{0}; ii<N; ++ii)
		{
			lower_indices[ii] = ii;
			upper_indices[ii] = ii+1;
		}
		for (SizeT ii{N}; ii<ParC::num_procs; ++ii)
		{
			lower_indices[ii] = N;
			upper_indices[ii] = N;
		}
	}

	return std::make_tuple(lower_indices, upper_indices);
}


// who owns thing k?
template <SizeT N>
int Possessor(unsigned k)
{
	static bool computed{false};
	static std::vector<int> who(N); // vector of size numprocs

	if (!computed)
	{
		const auto bounds = PartitionOf(N);
		const auto& lower = std::get<0>(bounds);
		const auto& upper = std::get<1>(bounds);
		const int num_procs = ParC::num_procs;

		for (SizeT i{0}; i<N; ++i)
			for (int j{0}; j<ParC::num_procs; ++j)
				if (lower[j]<=i && i<upper[j])
				{
					who[i] = j;
					break;
				}
		computed = true;
	}

	return who[k];
}

template<SizeT N>
bool IsPossessor(int k)
{
	return Possessor<N>(k)==ParC::my_id;
}


template<SizeT N, typename T>
void LU_InPlace_Col_MPI(Matrix<N,N,T> & A)
{
	// everyone gets the entire matrix.  
	// this is incorrect, each process needs only its own columns
	DistributeMatrixAllAll(A); 
	

	for (unsigned k=0; k<N-1; ++k) //no need to do the Nth iteration.
	{
		if (IsPossessor<N>(k)){ 
			for (unsigned i=k+1; i<N; ++i)
			{
				A[i][k] /= A[k][k];
			}
		}

		// broadcast L column k to all.
		for (unsigned i=k+1; i<N; ++i)
		{
		// in principle, send only to those processes which still need to do work
			// this bcast sends to too many people
			// it also is garbage, because it sends one-at-a-time, which just kills.
			MPI_Bcast(&A[i][k], 1, NumTraits<T>::MPI_Type, Possessor<N>(k), MPI_COMM_WORLD);
		}

		//do the gaussian elimination on columns owned by this process.
		for (int j=k+1; j<N; ++j)
		{
			for (int i=k+1; i<N; ++i)
			{
				if (IsPossessor<N>(j)){ // only do the math for the columns owned by this process.
					A[i][j] -= A[i][k]*A[k][j];
				}
			}
		}
	}

	// at this point, each process has all L entries, and its own columns of U.  they need to share their columns of U with each other.
	for (int k=0; k<N; ++k)
	{
		for (int i=1; i<=k; ++i) // everyone already agrees on the first row.  it never changes
			MPI_Bcast(&A[i][k], 1, NumTraits<T>::MPI_Type, Possessor<N>(k), MPI_COMM_WORLD);
	}
}




template<SizeT N, typename T>
void LU_InPlace_Row_MPI(Matrix<N,N,T> & A)
{
	// everyone gets the entire matrix.  
	// this is incorrect, each process needs only its own rows at first
	DistributeMatrixAllAll(A); 
	

	for (unsigned k=0; k<N-1; ++k) //no need to do the Nth iteration.
	{
		MPI_Bcast(&A[k][k], N-k, NumTraits<T>::MPI_Type, Possessor<N>(k), MPI_COMM_WORLD);

		for (unsigned i=k+1; i<N; ++i)
		{
			if (IsPossessor<N>(i)) // only do the math for the columns owned by this process.
			{
				A[i][k] /= A[k][k];
			}
		}

			//do the gaussian elimination on columns owned by this process.
		for (unsigned i=k+1; i<N; ++i)
		{
			if (IsPossessor<N>(i))
				for (int j=k+1; j<N; ++j)
					A[i][j] -= A[i][k]*A[k][j];
		}
		
	}

	// at this point, each process has all L entries, and its own columns of U.  they need to share their columns of U with each other.
	for (int k=1; k<N; ++k)
	{
			MPI_Bcast(&A[k][0], k+1, NumTraits<T>::MPI_Type, Possessor<N>(k), MPI_COMM_WORLD);
	}
}




} // namespace


