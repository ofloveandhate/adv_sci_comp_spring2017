/**
 \file newton.hpp

 Dani Brake, 2017
 University of Notre Dame
 */

#pragma once

#include <stdexcept>
#include <functional>
#include <sstream>


namespace advscicomp {

/**
 a generic implementation of a single newton iteration, feeding it the two functions for
 function evaluation, and its derivative.
 the number type to be used is an inferred template argument.
 */
template<typename T, typename FuncT>
T NewtonIteration(T const& x, FuncT func, FuncT deriv)
{
	return x - func(x)/deriv(x);
}

/**
a generic implementation of newton's method, feeding it the two functions for
function evaluation, and its derivative.
the number type to be used is an inferred template argument.


\param x0 The seed for the algorithm
\param iterations The maximum number of permitted iterations
\param tolerance How close we want two consecutive iterations to be, to call it successful
\param func The function we are finding roots of.  This is an evaluable object, probably a free function.
\param deriv The derivative of `func`.  YOU must ensure that it is in fact the derivative.

 \throws runtime_error, if number of iterations exceeds max permitted.
 */
template<typename T, typename FuncT>
T NewtonsMethod(T const& x0, unsigned iterations, double tolerance, FuncT func, FuncT deriv)
{
	using std::abs; // so that the compiler finds the correct abs function, uses ADL.
	T x_prev = x0;  // initialize the state variable
	for (unsigned ii=0; ii<iterations; ++ii)
	{
		T x_next = NewtonIteration(x_prev, func, deriv); // compute the next iteration

		// if converged, then done, return the value
		if ( abs(double(x_next - x_prev)) < tolerance)   // uses the double conversion here for the number type T
			return x_next;

		x_prev = x_next; // update, since didn't converge
	}

	std::stringstream err_msg;
	err_msg << "too many iterations in newton's method, last approximation was " << x_prev;
	throw std::runtime_error(err_msg.str());
	// got this far, so didn't converge.
	//must have taken too many iterations.
}


}

