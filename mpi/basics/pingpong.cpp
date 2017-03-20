// the canonical ping pong game implemented for 2 processes
// dani brake
// spring 2017

enum {Ping, Pong};

#include <mpi.h>
#include <iostream>

int main(int argc, char** argv)
{
	MPI_Init(&argc, &argv);
	int my_id;
	MPI_Comm_rank(MPI_COMM_WORLD, &my_id);

	MPI_Status statty_mc_gatty;

	int num_iterations = 10;

	int my_int = 5 + my_id;

	for (int ii = 0; ii < num_iterations; ++ii)
	{
		if (my_id==0)
		{
			MPI_Send(&my_int, 1, MPI_INT, 1, Ping, MPI_COMM_WORLD);
			std::cout << "ping\n";
			MPI_Recv(&my_int, 1, MPI_INT, 1, Pong, MPI_COMM_WORLD,&statty_mc_gatty);
			std::cout << "pong\n";
		}
		else if (my_id==1)
		{
			MPI_Recv(&my_int, 1, MPI_INT, 0, Ping, MPI_COMM_WORLD,&statty_mc_gatty);
			MPI_Send(&my_int, 1, MPI_INT, 0, Pong, MPI_COMM_WORLD);
			
		}
	}

	MPI_Finalize();
	return 0;
}