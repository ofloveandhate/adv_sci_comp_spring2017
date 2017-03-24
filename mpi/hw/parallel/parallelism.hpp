// some helper data types, to make parallelism a little simpler to work with.


#pragma once

#include <mpi.h> // access to the MPI library
#include <complex>


namespace advscicomp{


struct ParallelismConfig
{
	static int my_id;
	static int num_procs;
	static int head;
	static void Init(int *argc, char*** argv)
	{
		MPI_Init(argc, argv);

		MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
		MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
		head=0;
	}


	static void Finalize()
	{
		MPI_Finalize();
	}

	enum Tag { Raspberry = 1000};
};

int ParallelismConfig::my_id = -1;
int ParallelismConfig::num_procs = -1;
int ParallelismConfig::head = -1;



template <typename T>
struct NumTraits
{};

template<>
struct  NumTraits<double>
{
	static const auto MPI_Type = MPI_DOUBLE;
};


template<>
struct  NumTraits<std::complex<double>>
{
	static const auto MPI_Type = MPI_CXX_DOUBLE_COMPLEX;
};



}

