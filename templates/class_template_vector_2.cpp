#include "class_template_vector_2.hpp"

#include <iostream>

int main()
{
	advscicomp::vector<int> my_vector1(1); // col_major, uses the heap (default)

	advscicomp::vector<double, advscicomp::row_major> my_vector2(1); // row_major, uses the heap (default)
	advscicomp::vector<double, advscicomp::row_major, advscicomp::stack> my_vector3(1); // row_major, uses the stack

	advscicomp::vector<> fully_default(100);

	std::cout << my_vector1.size() << std::endl;

	return 0;
}