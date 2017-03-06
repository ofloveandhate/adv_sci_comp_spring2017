#include <iostream>
#include <mpi.h>

int main(int argc, char ** argv){
	int my_id, totalnodes;
	int sum,startval,endval,accum;
	MPI_Status status;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &totalnodes);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
	
	sum = 0;
	startval = 1000*my_id/totalnodes+1;
	endval =   1000*(my_id+1)/totalnodes;

	for(int i=startval;i<=endval;i=i+1)
		sum = sum + i;

	if(my_id!=0)
		MPI_Send(&sum,1,MPI_INT,0,1,MPI_COMM_WORLD);
	else
		for(int j=1; j<totalnodes; ++j){
			MPI_Recv(&accum,1,MPI_INT,j,1,MPI_COMM_WORLD, &status);
			sum += accum;
		}

	if(my_id == 0)
		std::cout << "The sum from 1 to 1000 is: " << sum << std::endl;	

	MPI_Finalize();
}		
