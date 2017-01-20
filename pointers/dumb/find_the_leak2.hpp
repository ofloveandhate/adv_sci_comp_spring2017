// find_the_leak2.hpp
// has at least one memory leak, and you need to find them.
// for 40212 / 60212 spring 2017

// dani brake 
// notre dame
// acms
// dbrake@nd.edu


#pragma once

#include <iostream>
#include <random>


namespace advscicomp {


	void f();

	void f(int *i);

	int* g();

	int* g(int *i);

}

