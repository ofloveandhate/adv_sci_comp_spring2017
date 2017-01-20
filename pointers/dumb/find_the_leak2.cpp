#include "find_the_leak2.hpp"

namespace advscicomp {
	void f()
	{

	}

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
		std::cout << *g() << " ";

	std::cout << '\n';


	f();

	g();

	f(g());

	f(g(g()));

}