// find_the_leak1.hpp
// has at least one memory leak, and you need to find them.
// for 40212 / 60212 spring 2017

// dani brake 
// notre dame
// acms
// dbrake@nd.edu

#pragma once

#include <memory>
#include <iostream>

namespace advscicomp {

	using LargeComplexT = int;

	class Yasreet 
	{
		std::unique_ptr<LargeComplexT> large_thing_;

	public:

		// make a Yasreet
		Yasreet() : large_thing_(std::make_unique<LargeComplexT>())
		{}

		// make a Yasreet
		Yasreet(LargeComplexT i) : large_thing_(std::make_unique<LargeComplexT>(i))
		{}

		// copy constructor
		Yasreet(Yasreet const& y) : Yasreet()
		{
			*large_thing_ = *y.large_thing_;
		}

		Yasreet& operator=(Yasreet const& y)
		{
			*large_thing_ = *(y.large_thing_);
			return *this;
		}


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

		~Yasreet() = default;
		// ~Yasreet()
		// {
		// 	delete large_thing_;
		// }
	};


	inline
	std::ostream& operator<<(std::ostream & out, Yasreet const& y)
	{
		out << y.GetField();
		return out;
	}

}

