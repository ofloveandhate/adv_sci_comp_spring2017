// find_the_leak1.hpp
// has at least one memory leak, and you need to find them.
// for 40212 / 60212 spring 2017

// dani brake 
// notre dame
// acms
// dbrake@nd.edu

#pragma once

#include <iostream>

namespace advscicomp {

	using LargeComplexT = int;

	class Yasreet 
	{
		LargeComplexT *large_thing_;

	public:

		// make a Yasreet
		Yasreet() : large_thing_(new LargeComplexT)
		{}

		// make a Yasreet
		Yasreet(LargeComplexT i) : large_thing_(new LargeComplexT(i))
		{}

		// set member variable of a Yasreet
		void SetField(LargeComplexT i)
		{
			*large_thing_ = i;
		}

		// get (const) member variable of a Yasreet
		const LargeComplexT& GetField() const
		{
			return *large_thing_;
		}

	};


	inline
	std::ostream& operator<<(std::ostream & out, Yasreet const& y)
	{
		out << y.GetField();
		return out;
	}

}

