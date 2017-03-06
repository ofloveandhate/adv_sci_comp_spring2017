#include <stdio.h> 
#include "mpi.h" 
int main(int argc, char** argv)
{      


  int my_rank, nprocs, recv_count; 
  MPI_Request  request;
  MPI_Status status;
  double s_buf[100], r_buf[100]; 

  MPI_Init(&argc, &argv); 
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs); 

  if (my_rank==0){ 
   MPI_Irecv(r_buf, 100, MPI_DOUBLE, 1, 22, MPI_COMM_WORLD, &request); 
   MPI_Send(s_buf, 100, MPI_DOUBLE, 1, 10, MPI_COMM_WORLD);
   MPI_Wait(&request, &status);
 } 
 else if(my_rank == 1){
  MPI_Irecv(r_buf, 100, MPI_DOUBLE, 0, 10, MPI_COMM_WORLD, &request);
  MPI_Send(s_buf, 100, MPI_DOUBLE, 0, 22, MPI_COMM_WORLD);
  MPI_Wait(&request, &status);
}
MPI_Get_count(&status, MPI_DOUBLE, &recv_count);
printf("proc %d, source %d, tag %d, count %d\n", my_rank, 
 status.MPI_SOURCE, status.MPI_TAG, recv_count); 
MPI_Finalize(); 
} 
