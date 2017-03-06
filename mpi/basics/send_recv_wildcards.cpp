#include <stdio.h>
#include "mpi.h"

int main(int argc, char** argv)
{   
    int my_rank, numbertoreceive[10], numbertosend[3]={73, 2, -16};
    int  recv_count, i;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank==0){
        MPI_Recv( numbertoreceive, 3, MPI_INT, MPI_ANY_SOURCE,  MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        printf("status.MPI_SOURCE = %d\n", status.MPI_SOURCE);
        printf("status.MPI_TAG = %d\n", status.MPI_TAG);
        printf("status.MPI_ERROR = %d\n", status.MPI_ERROR);

        MPI_Get_count(&status, MPI_INT, &recv_count);
        printf("Received %d pieces of data:\n",  recv_count);
        for(i = 0; i < recv_count; i++)
            printf("recv[%d] = %d\n", i, numbertoreceive[i]);
    }
    else 
        MPI_Send( numbertosend, 3, MPI_INT, 0, 10, MPI_COMM_WORLD);

    MPI_Finalize();
    return 0;
}
