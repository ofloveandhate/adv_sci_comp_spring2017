
#include <iostream>


namespace advscicomp{

	/**
	makes a pointer to an object.  a basic demo
	*/
	void AssignToExistingObject()
	{
		int *ip = nullptr; // make a pointer to an integer
		int i = 42; // make an integer
		ip = &i; // now ip points to i;

		++(*ip);

		std::cout << i << '\n'; // should print 43
	}

	/**
	this function deliberately leaks a block of size n
	*/
	void LeakyArrayF(unsigned n)
	{
		int *arp;
		arp = new int[n]; // now we have a manually-managed array of 33 integers.
		// failure to delete[] arp will result in a leak ... silently.

		for (unsigned ii=0; ii<n; ++ii)
			arp[ii] = 2*ii;

		for (unsigned ii=0; ii<n; ++ii)
			std::cout << arp[ii] << " ";
		std::cout << '\n';
	}


	/**
	a factory function
	*/
	int* ReturnsAPointer()
	{
		return new int(332);
	}


	/**
	to me, this function is really scary.  why does it delete it?
	*/
	void DoSomethingAndDelete(int* i)
	{
		std::cout << *i-1 << '\n';
		delete i;
	}



	int * MakeArray(unsigned n)
	{
		return new int[n];
	}

	int* HighLevelF()
	{
		return MakeArray(rand()%100+1);
	}
}

int main()
{

	using namespace advscicomp;

	AssignToExistingObject();

	LeakyArrayF(10);
	
	int *i = ReturnsAPointer(); // how do you know it returns a pointer?  
	// DOCUMENTATION and GOOD NAMES

	DoSomethingAndDelete(i);
	// again, this is scary.  now I have `i`, and it points to dead memory.  eww.


	int * arr = MakeArray(100);
	// now arr points to an array of 100 integers. fwiw.

	int* brr = HighLevelF();
	// brr also points to an array, of size...  uh oh

	delete[] arr;  // call the array form if you allocated an array.
	delete[] brr;  // similarly


	return 0;
}


