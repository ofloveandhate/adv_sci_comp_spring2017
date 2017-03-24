


#include <iostream>
#include <iomanip>

#include <assert.h>

#include <sstream>
#include <fstream>


#include "lu_parallel.hpp"

#include <chrono>

namespace performance
{
	using namespace advscicomp;

	template<SizeT N>
	struct Tester
	{

		static void RunHead(unsigned iterations_per_a, unsigned num_a)
		{
			ResetTimers();
			for (unsigned ii=0; ii<num_a; ++ii)
			{
				NewA();
				for (unsigned jj=0; jj<iterations_per_a; ++jj)
					SingleIterationHead();
			}
			PrintTimers();
		}



		static void RunWorker(unsigned iterations_per_a, unsigned num_a)
		{
			for (unsigned ii=0; ii<num_a; ++ii)
				for (unsigned jj=0; jj<iterations_per_a; ++jj)
					SingleIterationWorker();
		}


		static 
		void SingleIterationHead()
		{
			auto A = A_original;

			std::chrono::time_point<std::chrono::steady_clock> start_time = std::chrono::steady_clock::now();
				LU_InPlace_Col_MPI(A);
			etime += std::chrono::steady_clock::now() - start_time;
			++count;
		}

		static
		void SingleIterationWorker()
		{
			LU_InPlace_Col_MPI(A_original);
		}

		static void NewA()
		{
			A_original = RandomMat<N>();
		}

		



		static void ResetTimers()
		{
			etime = std::chrono::microseconds{0};
			count = 0;
		}

		static void PrintTimers()
		{
			std::cout << "matrix size: " << N << '\n';
			std::cout << "total time to decompose: " << std::chrono::duration_cast<std::chrono::microseconds>(etime).count() << " microseconds" << '\n';
			std::cout << "matrices decomposed: " << count << '\n';
		}

		static Matrix<N,N> A_original;
		static std::chrono::duration<double> etime;
		static unsigned count;
	};

	template<SizeT N> Matrix<N,N> Tester<N>::A_original = RandomMat<N>();
	template<SizeT N> std::chrono::duration<double> Tester<N>::etime = std::chrono::microseconds{0};
	template<SizeT N> unsigned Tester<N>::count = 0;
}




int main(int argc, char** argv)
{
	using PC = advscicomp::ParallelismConfig;
	PC::Init(&argc, &argv);

	if (PC::my_id == PC::head)
		performance::Tester<200>::RunHead(4,5);
	else
		performance::Tester<200>::RunWorker(4,5);

	PC::Finalize();
	return 0;
}
