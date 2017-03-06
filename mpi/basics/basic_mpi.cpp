#include<iostream>

#include <mpi.h>

int main(int argc, char** argv)
{
  MPI_Init(&argc, &argv);
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
  std::cout << rank << std::endl;
  MPI_Finalize();

  return 0;
}

