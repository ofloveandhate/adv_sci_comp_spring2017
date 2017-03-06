#include <stdio.h>
#include "mpi.h"

/* process 0 receive a number from and send a number from process 1.
     process 1 receive a number from and send a number to process 0   
*/ 
int     main(int argc, char** argv)
{          /**** sample_deadlock.c   *****/
    int my_rank, numbertoreceive, numbertosend = -16;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank==0){
            MPI_Recv( &numbertoreceive, 1, MPI_INT, 1,  20, MPI_COMM_WORLD, &status);
            MPI_Send( &numbertosend, 1, MPI_INT, 1,    10, MPI_COMM_WORLD);
     }
    else  if(my_rank == 1)
    {
             MPI_Recv( &numbertoreceive, 1, MPI_INT, 0,  10, MPI_COMM_WORLD, &status);
             MPI_Send( &numbertosend,     1, MPI_INT, 0, 20, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}
