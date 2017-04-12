// replicating results from 
// http://www.drdobbs.com/parallel/eliminate-false-sharing/217500206?pgno=1
// by Herb Sutter, on false sharing
//
// he uses an abstract pool of threads, we will use openmp

#include <cstdlib>

#include <omp.h>
#define MAX_NUM_THREADS 64


int main(int argc, char ** argv)
{
  long DIM = 10000;

  // Example 3: incorporated random reads
  //
  int odds=0;
  int result[MAX_NUM_THREADS];
  int *matrix = new int[DIM*DIM]; // represent the square matrix linearly.
  for (long i=0; i<DIM*DIM; ++i)
    matrix[i] = rand();

  // Each of P parallel workers processes 1/P-th
  // of the data; the p-th worker records its
  // partial count in result[p]
  #pragma omp parallel
  {
    int p = omp_get_thread_num();
    int local = 0;
    result[p] = 0;
    #pragma omp for
    for( long i = 0; i < DIM; ++i )
    {
      for (long k = 0; k<100; ++k)
      for( long j = 0; j < DIM; ++j )
        if ( matrix[i*DIM + j] % 2 != 0 )
        {
          if (p%2) // half of accesses are reads
            ++result[p];
          else
            local += result[p];
        }
    }

    #pragma omp atomic
      odds += result[p];
  }

 

}
