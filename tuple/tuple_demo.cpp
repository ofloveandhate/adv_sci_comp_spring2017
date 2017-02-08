// demonstrates some usage of tuples

#include <tuple>
#include <string>
#include <iostream>


enum class Animal
{
	Canary,
	Rabbit, 
	Tiger
};


std::tuple<int, std::string>  foo( Animal a)
{
	switch(a)
	{
		case Animal::Canary:
			return std::make_tuple(110, "tweet tweet");
		break;
		case Animal::Rabbit:
			return std::make_tuple(111, "It's duck season");
		break;
		case Animal::Tiger:
			return std::make_tuple(100, "it's greeeeat");
		break;
	}

}

void r()
{
	return 7;
}

int main()
{
	r();
	
	int color;
	std::string catchphrase;

	std::tie(catchphrase, color) = foo( Animal::Canary);

	std::cout << color << " " << catchphrase << '\n';
	return 0;
}








