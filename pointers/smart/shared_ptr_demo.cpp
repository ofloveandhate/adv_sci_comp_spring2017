// use c++14 to compile this, ftw

#include <iostream>
#include <memory>


namespace advscicomp {

	using ComplicatedType = int;


	std::shared_ptr<ComplicatedType> CallSharedFactory()
	{
		return std::make_shared<ComplicatedType>(-rand()%1000);
	}


	void TakesShared(std::shared_ptr<ComplicatedType> const& c)
	{
		std::shared_ptr<ComplicatedType> d = c; // i don't know why you are making a copy, but ok

		std::cout << *c << " "  <<  c.use_count() << " " << d.use_count() << '\n';
	}

}

int main()
{
	srand(time(NULL)); rand();

	using namespace advscicomp;
	auto sp = CallSharedFactory();

	std::cout << sp.use_count() << " " << *sp << '\n'; 

	auto sp2 = sp;

	std::cout << sp.use_count() << '\n'; 

	sp2.reset();

	std::cout << sp.use_count() << " " << *sp << '\n'; 

	ComplicatedType *raw = new ComplicatedType(13);
	std::shared_ptr<ComplicatedType> new_shared_owner(raw); // raw is now owned by new_shared_owner

	TakesShared(new_shared_owner);
	TakesShared(sp);


	return 0;
}

