// for fun reading, see
// https://groups.google.com/forum/#!topic/comp.lang.c++/Rp_ME2uPLUI


// use c++14 to compile this, ftw

#include <iostream>
#include <memory>

namespace advscicomp{
	
	
	using ComplicatedType = int;

	/**
	Merely a factory for making modern pointer-managed dynamically allocated objects of complicated type.
	*/
	std::unique_ptr<ComplicatedType> CallUniqueFactory()
	{
		return std::make_unique<ComplicatedType>(141);
	}



	std::unique_ptr<ComplicatedType[]> ReturnsPtrToArray(unsigned n)
	{
		return std::make_unique<ComplicatedType[]>(n); // makes an array of size n.
		// don't worry, delete[] is called on it!
	}


	void DoSomethingAndConsume(std::unique_ptr<ComplicatedType> && ip)
	{
		std::cout << *ip-1 << '\n';
	}

}

int main()
{

	using namespace advscicomp;

	auto ctp = CallUniqueFactory(); // no need to delete it, ever.  done for you!

	auto arrp = ReturnsPtrToArray(100); //arrp still doesn't know how big it is...

	DoSomethingAndConsume(std::move(ctp)); // leaves ctp in a valid state, but object it is managing is deleted.




	return 0;
}


