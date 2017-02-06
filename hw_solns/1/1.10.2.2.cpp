#include <iostream>
#include <memory>



int main()
{

	// make a small program that creates arrays on the stack and on the heap (using allocation).  Use valgrind to check what happens when you do not delete them correctly

using T = int;
	// stack
	T a[] = {1, 2, 3}; // compiler figures out size for you
	T b[10]; //10 ints of unspecified value;
	T c[11][5];  // an 11x5 array

	int N = 101;
	T *x = new int[N];

	T ** y = new int*[N];

	for (int ii=0; ii<N; ++ii)
		y[ii] = new int[N];

	y[1][1] = 3;

	for (int ii=0; ii<N; ++ii)
		delete[] y[ii];
	
	delete[] y;


	delete[] x; // what happens if you don't use [] with delete?
	return 0;	
}

