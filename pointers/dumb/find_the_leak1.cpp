#include "find_the_leak1.hpp"



int main()
{
	using Yas = advscicomp::Yasreet;

	Yas y1, y2(3);

	Yas y3 = y2;

	std::cout << y1 << " " << y2 << " " << y3 << std::endl;

	y2.SetField(42);

	std::cout << y1 << " " << y2 << " " << y3 << std::endl;

	y1 = y2;

	std::cout << y1 << " " << y2 << " " << y3 << std::endl;

	return 0;
}


