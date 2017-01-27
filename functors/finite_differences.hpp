

#pragma once

#include <cmath>

namespace advscicomp {

	double sin_plus_cos(double x)
	{
		return sin(x) + cos(x);
	}


	
	// a functor
	struct sc_f 
	{
		double operator() (double x) const
		{
			return sin(x) + cos(x);
		}
	};

	// a stateful functor
	class psc_f 
	{
	public: 
		psc_f(double alpha) : alpha(alpha) {}
		double operator() (double x) const
		{
			return sin(alpha * x) + cos(x);
		}
	private:
		double alpha; // the state
	};



	template< typename F, typename T>
	T inline fin_diff( F f, const T& x, const T& h)
	{
		return (f(x+h) - f(x)) / h;
	}


	template <typename F, typename T>
	class derivative 
	{
	public: 
		derivative(const F& f, const T& h) : f(f), h(h) {}

		T operator() (const T& x) const
		{
			return ( f(x+h) - f(x)) / h;
		}
	private:
		const F& f;
		T	h;
	};  //  this produces functors approximating f'





	template <typename F, typename T, unsigned N>
	class nth_derivative
	{
		using prev_derivative = nth_derivative<F, T, N-1>;
	public:
		nth_derivative(const F& f, const T& h) : h(h), fp(f, h) {}

		T operator() (const T& x) const
		{
			return (fp(x+h) - fp(x)) / h;
		}
	private:
		T	h;
		prev_derivative fp;
	}; // how to stop the recursion?????



	// the base case to prevent infinite recursion.
	// specialize for base case
	// see, the N is missing?  it's been specialized
	template <typename F, typename T>
	class nth_derivative<F, T, 1>
	{
	public:
		nth_derivative(const F& f, const T& h) : h(h), f(f) {}

		T operator() (const T& x) const
		{
			return (f(x+h) - f(x)) / h;
		}
	private:
		T		h;
		const F& 	f;
	}; 



	// the make function from p 153
	template <unsigned N, typename F, typename T>
	nth_derivative<F, T, N>  // return type
	make_nth_derivative(const F& f, const T& h)
	{
		return nth_derivative<F, T, N>(f, h);
	}





}


