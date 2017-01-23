/**
\file newton_rational.cpp

source file, demonstrating some things about templates and instantiation

Dani Brake, 2017
University of Notre Dame
*/



#include "rational.hpp"
#include "newton.hpp"
#include <iostream>

// the function to feed to newton's method.
// change to whatever you want, but f_prime (below) must match.
template<typename T>
T f(T const& x)
{
	return -(x-1) + pow(x-1,4) + x/2*(x+1);
}

// this function MUST be the derivative of f, or things go wrong
//  is this correct?
template<typename T>
T f_prime(T const& x)
{
	return 1 + 4*pow(x-1,3);
}


int main() {
	using T = advscicomp::Rational<>; // changing T here changes the mode of operation.

	// your mission, should you choose to accept it, is to complete the Rational class, so that it computes correctly.
	try{
		T result = NewtonsMethod( T(0)/T(1), 5, 1e-5, f<T>, f_prime);
		std::cout << "result is " << result << ", and in double is " << double(result) << std::endl;
	}
	catch (const std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
}
