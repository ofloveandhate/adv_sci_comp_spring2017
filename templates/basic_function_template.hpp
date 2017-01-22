// a header containing a basic function template example

#pragma once

#include <iostream>

namespace advscicomp {


	/**
	\brief Generic implementation of max.

	\see Discovering Modern C++, page 107
	*/
	template <typename T>
	T max(T a, T b)
	{
		if (a > b)
			return a;
		else
			return b;
	}
}
