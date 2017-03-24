


#include <iostream>
#include <iomanip>

#include <assert.h>

#include <sstream>
#include <fstream>

#include "../serial/lu.hpp"
#include "lu_parallel.hpp"


namespace test
{
	using namespace advscicomp;


	constexpr SizeT tested_size = 50;


	namespace parallel
	{

		void LU_Col_InPlaceProducesOriginalMatrix(double threshold = 1e-7)
		{
			const auto A_original = RandomMat<tested_size>();
			auto A = A_original;
			auto A2 = A_original;


			LU_InPlace_Col_MPI(A);



				auto unpacked_result = UnpackToLU(A);
				const auto& L = std::get<0>(unpacked_result);
				const auto& U = std::get<1>(unpacked_result);

				auto checkme = L*U;

			if (ParC::my_id == ParC::head)
			{
				std::cout << "A = " << A_original << '\n';

				LU_Col_InPlace(A2);
				std::cout << "serial_decomposed = " << A2 << '\n';
				std::cout << "parallel_decomposed = " << A << '\n';
				using std::abs;
				for (unsigned ii{0}; ii<tested_size; ++ii)
					for (unsigned jj{0}; jj<tested_size; ++jj)
						if (abs(checkme[ii][jj] - A_original[ii][jj]) > threshold)
						{
							std::cout << "fail at A[" << ii << "][" << jj << "]\n";
						}
			}
		}

		void RunSuite()
		{
			LU_Col_InPlaceProducesOriginalMatrix();
		}



	}
}




int main(int argc, char** argv)
{

	advscicomp::ParallelismConfig::Init(&argc, &argv);

	test::parallel::RunSuite();

	advscicomp::ParallelismConfig::Finalize();
	return 0;
}
