#include "find_the_leak2.hpp"

namespace advscicomp {
	void f()
	{

	}

	// assume i actually points somewhere
	void f(int *i)
	{
		delete i;
	}

	int* g()
	{
		static std::random_device rd;
		static std::mt19937 gen(rd());
		static std::uniform_int_distribution<int> dis(-10, 10);

		return new int(dis(gen));
	}

	int* g(int *i)
	{
		int *r = new int(*i+5);
		return r;
	}

}

int main()
{
	using advscicomp::f;
	using advscicomp::g;
	
	for (int ii=0; ii<5; ++ii)
	{
		int* p = g();
		std::cout << *p << " ";
		delete p;
	}

	std::cout << '\n';


	f(); // does nothing, is ok

	int* q = g();
	delete q;
	
	f(g()); // f consumes g, so ok

	// f(g(g())); // the inner g was leaked.
	int* p = g();
	f(g(p));
	delete p;
}