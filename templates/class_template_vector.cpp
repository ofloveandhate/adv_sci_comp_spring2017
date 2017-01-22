#include "class_template_vector.hpp"

#include <iostream>

int main()
{
	advscicomp::vector<int> my_vector(1);

	std::cout << my_vector.size() << std::endl;

	return 0;
}