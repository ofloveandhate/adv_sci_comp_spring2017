#include "basic_function_template.hpp"


int main()
{
	std::cout << 
		advscicomp::max(1,2) << " " << 
		advscicomp::max(0.1, 100.122) << " " << 
		advscicomp::max("asdf", "qwer") << '\n';
		
	return 0;
}

