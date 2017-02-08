// solution for
// problem 3.11.1 from Discovering Modern C++
//
// dani brake
// notre dame
// acms
// 2017
// danielthebrake@gmail.com

#include <assert.h>
#include <string>
#include <sstream>

namespace advscicomp{

template<typename T>
std::string to_string(T const& t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

}


int main()
{
	using advscicomp::to_string;
	std::string teststring = "a b asdf";
	assert( to_string(teststring) == teststring);

	int i = 123;
	assert( to_string(i) == "123");
}