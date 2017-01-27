#include "finite_differences.hpp"

#include <iostream>


using namespace advscicomp;



void seventh_using_plain_template()
{
	auto psc_o = psc_f(2.0);

	nth_derivative<psc_f, double, 7> d7_psc_o(psc_o, 0.00001);
	std::cout << d7_psc_o(2.) << std::endl;
}

void seventh_using_make_fn()
{
	auto psc_o = psc_f(2.0);
	auto d7_psc_o = make_nth_derivative<7>(psc_o, 0.00001);
	std::cout << d7_psc_o(2.) << std::endl;
}


void still_takes_plain_functions()
{
	auto psc_o = psc_f(2.0);
	auto d7_psc_o = make_nth_derivative<7>(sin_plus_cos, 0.00001);
	std::cout << d7_psc_o(2.) << std::endl;
}

int main()
{
	seventh_using_plain_template();
	seventh_using_make_fn();
	still_takes_plain_functions();
}

