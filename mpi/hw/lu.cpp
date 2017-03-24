
// base LU decomposition algorithm, to parallelize

#include <mpi.h> // access to the MPI library

#include <array> // c++11 array
#include <iostream> 
#include <iomanip>
#include <random>
#include <tuple>
#include <assert.h>

namespace advscicomp{


template<typename T>
struct Random
{
	static 
	T Generate()
	{
		static_assert(std::is_arithmetic<T>::value, "must use an arithmetic type");
		return Generate(std::is_integral<T>());
	}


private:

	static
	T Generate(std::true_type)
	{
		static std::random_device rd;
		static std::default_random_engine gen(rd());
		static std::uniform_int_distribution<T> dist(std::numeric_limits<T>::min(),std::numeric_limits<T>::max());
		return dist(gen); 
	} 

	static
	T Generate(std::false_type)
	{
		static std::random_device rd;
		static std::default_random_engine gen(rd());
		static std::uniform_real_distribution<T> dist(T{-1},T{1});
		return dist(gen); 
	} 

   
};

using SizeT = unsigned long;

template<SizeT M, SizeT N, typename T = double>
using Matrix =  std::array<std::array<T, N>, M>;


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




} // namespace





namespace test
{
	using namespace advscicomp;

	constexpr SizeT tested_size = 6;



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

