// some trivial matrix-y code from Zhilang Xu's previous sections of 40212.


#include <cstdio>
#include <iostream>
#include <sys/types.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/utsname.h>
#include <unistd.h>

#include "mpi.h"

#define  M 1000
#define  N  10000

using namespace std; 

int main (
	int    argc,
	char*  argv[])
{
	int    my_rank = -1, total, i, j, k;
    struct utsname Uts;
    double  **A, **B, **C;

    MPI_Init(&argc, &argv); 
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &total);

    uname(&Uts);
    usleep(10);

        // printf("#\tHostname                 = %s\n",Uts.nodename);
        // printf("#\tCPU Type                 = %s\n",Uts.machine);
        // printf("#\tOperating System         = %s\n",Uts.sysname);
        // printf("#\tOS Release               = %s\n",Uts.release);
        // printf("#\tOS Version               = %s\n",Uts.version);

        // printf("Hello from node %d within total proc %d on Hostname = %s\n",
        //     my_rank, total, Uts.nodename);

    A = new double*[M]; 
    for(i = 0; i < M; i++)
        A[i] = new double[M]; 

    B = new double*[M]; 
    for(i = 0; i < M; i++)
        B[i] = new double[M]; 

    C = new double*[M]; 
    for(i = 0; i < M; i++)
        C[i] = new double[M]; 

    for(i = 0; i < M; i++)
    {
        for(j = 0; j < M; j++)
        {
            A[i][j] = my_rank + i + j ; 
            B[i][j] = 2*my_rank + i + j ; 
        }
    }

    for(i = 0; i < M; i++)
    {
        for(j = 0; j < M; j++)
        {
                // usleep(10);
            C[i][j] = 0.0; 
            for(k = 0; k < M; k++)
            {
                C[i][j] += A[i][k] * B[k][j]; 
            }
        }
    }

    cout<<"Hello from proc " <<  my_rank <<" within total proc "<< total 
    <<" on Hostname: "<< Uts.nodename <<endl;  
    cout <<"process "<<my_rank <<" C[0][0] "<< C[0][0] <<endl;

    MPI_Finalize();  /* Shut down MPI */
    return 0;
}
