#include "basic_function_template.hpp"


int main()
{
	std::cout << 
		advscicomp::max(1,2) << " " << 
		advscicomp::max(0.1, 100.122) << " " << 
		advscicomp::max("asdf", "qwer") << '\n';

std::cout << '\n';
	advscicomp::g(-1, 100);
	advscicomp::g(1, 200.11);
	advscicomp::g(1, -1010l);

std::cout << '\n';
	advscicomp::g(std::string("adam"), 100);
	advscicomp::g(std::string("zach"), 200.11);
	advscicomp::g(std::string("zadie"), -1010l);
std::cout << '\n';

 	return 0;
}

