// a simple program which does nothing other than prove we can 
// 1. include OpenMP
// 2. use a directive from it

#include <omp.h>

#include <stdio.h>


int main() {
#pragma omp parallel
    printf("Hello from thread %d, nthreads %d\n", omp_get_thread_num(), omp_get_num_threads());

}
