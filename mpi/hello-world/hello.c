#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
	
	int i, myid, ntasks;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);

	if (myid == 0) {
		printf("Total number of processes %d\n", ntasks);
	}

	printf("Hello MPI from process %d\n!", myid);
	MPI_Finalize();

	return 0;
}

