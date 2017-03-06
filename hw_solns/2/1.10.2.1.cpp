#include <iostream>
#include <memory>



int main()
{
	char c = 'T';
	// pointer to character
	char * pc1 = new char('T'); 
	char * pc2 = &c; 
	delete pc1;

	// array of 10 ints
	int ai[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
	int * pai = ai;


	//pointer to an array of character strings
	//what is a character string?
	//let's let that be a c++-string
	std::unique_ptr<std::string[]> pacs1(new std::string[5]);
	auto pacs2 = std::make_unique<std::string[]>(5);


	// pointer to pointer to character
	char ** p_p_c = new char*;
	*p_p_c = new char;
	**p_p_c = 'T';

	delete *p_p_c;
	delete p_p_c;


	// integer constant
	const int ci = 5;

	// pointer to integer constant

	int const* pci = & ci;

	int i = 102;

	// const pointer to integer
	const int *cpi = &i;

	return 0;	
}

