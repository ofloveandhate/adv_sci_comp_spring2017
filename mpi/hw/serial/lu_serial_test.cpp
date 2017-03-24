
// base LU decomposition algorithm, to parallelize



#include <array> // c++11 array
#include <iostream> 
#include <iomanip>


#include <assert.h>




#include "lu.hpp"




namespace test
{
	using namespace advscicomp;

	constexpr SizeT tested_size = 50;



	void mult()
	{
		auto A = RandomMat<tested_size>();
		auto B = RandomMat<tested_size,tested_size+1>();
		auto C = A*B;
		std::cout << "A = " << A <<'\n';
		std::cout << "B = " << B <<'\n';
		std::cout << "C = " << C <<'\n';
	}





	void CanMakeIdentity()
	{
		auto A = Identity<tested_size>();
	}


	void CanMakeRandom()
	{
		auto A = RandomMat<tested_size>();
		auto B = RandomMat<tested_size,4>();
	}


	void LU_RunsAtAll()
	{
		auto A = RandomMat<tested_size>();
		auto ellyou = LU(A);
	}

	void LU_InPlace_RunsAtAll()
	{
		auto A = RandomMat<tested_size>();
		LU_InPlace(A);
	}



	void LU_ProducesOriginalMatrix(double threshold = 1e-7)
	{
		auto A = RandomMat<tested_size>();

		auto ellyou = LU(A);
		const auto& L = std::get<0>(ellyou);
		const auto& U = std::get<1>(ellyou);

		auto checkme = L*U;

		using std::abs;
		for (unsigned ii{0}; ii<tested_size; ++ii)
			for (unsigned jj{0}; jj<tested_size; ++jj)
				assert(abs(checkme[ii][jj] - A[ii][jj]) < threshold);
	}


	void LU_InPlaceProducesOriginalMatrix(double threshold = 1e-7)
	{
		auto A_original = RandomMat<tested_size>();
		auto A = A_original;

		LU_InPlace(A);
		auto unpacked_result = UnpackToLU(A);
		const auto& L = std::get<0>(unpacked_result);
		const auto& U = std::get<1>(unpacked_result);

		auto checkme = L*U;

		using std::abs;
		for (unsigned ii{0}; ii<tested_size; ++ii)
			for (unsigned jj{0}; jj<tested_size; ++jj)
				assert(abs(checkme[ii][jj] - A_original[ii][jj]) < threshold);
	}


	void RunSuite()
	{
		CanMakeIdentity();
		CanMakeRandom();
		LU_RunsAtAll();
		LU_ProducesOriginalMatrix();
		LU_InPlaceProducesOriginalMatrix();
		std::cout << "\n\npassed checks!\n\n";
	}
}




int main()
{
	test::RunSuite();
	
	return 0;
}

