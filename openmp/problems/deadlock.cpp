// this code is provided specifically to demonstrate a deadlock
// in openmp.

// see, e.g.
// https://www.ibm.com/support/knowledgecenter/SSGH2K_13.1.2/com.ibm.xlc131.aix.doc/compiler_ref/prag_omp_critical.html

#include <omp.h>

#include <vector>
#include <iostream>

// uses unspecified name for critical region.
void foo()
{
	#pragma omp parallel
	#pragma omp critical
	{
		auto id = omp_get_thread_num();
		std::cout << "o,hai there, i'm " << id << '\n';
	}

}

// goes with foo above.
// uses an unspecified name for critical region.
void deadlockA()
{
	int sum{0}; 

	#pragma omp parallel for
	for (int ii=0; ii<100; ++ii)
	{
		#pragma omp critical
		{
			sum += ii;
			foo();
		}
	}
}


// slightly different than A.  causes deadlock
// even when using names for the critical sections
void deadlockB()
{
	#pragma omp parallel
	{
		#pragma omp critical(A)
		{
			#pragma omp critical(B)
			{
				std::cout << "whassup\n";
			}
		}
		#pragma omp critical(B)
		{
			#pragma omp critical(A)
			{
				std::cout << "ahoy\n";
			}
		}
	}

}



int main()
{
	deadlockB();


	return 0;
}
