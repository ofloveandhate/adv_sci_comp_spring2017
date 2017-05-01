#include <vector>
#include <iostream>
#include <cstdlib>

int main() {

  std::vector<int> v(100,0);
  std::cout << v.capacity() << std::endl;
  for (int ii=0; ii<=102; ++ii)
    v[ii] = rand();

  std::cout << "here\n";

  return 0;
}
