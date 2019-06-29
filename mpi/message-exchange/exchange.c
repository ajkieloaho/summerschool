#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>


int main(int argc, char *argv[])
{
    int i, myid, ntasks;
    int msgsize = 100000;
    int *message;
    int *receiveBuffer;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    /* Allocate message */
    message = (int *)malloc(sizeof(int) * msgsize);
    receiveBuffer = (int *)malloc(sizeof(int) * msgsize);
    /* Initialize message */
    for (i = 0; i < msgsize; i++) {
        message[i] = myid;
    }

    /* TODO: */
    /* Send and receive messages as defined in exercise */
    if (myid == 0) {
	MPI_Send(message, msgsize, MPI_INT, 1, 1, MPI_COMM_WORLD);
        printf("Rank %i received %i\n", myid, receiveBuffer[0]);
    } else if (myid == 1) {
	MPI_Recv(receiveBuffer, msgsize, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        printf("Rank %i received %i\n", myid, receiveBuffer[0]);
    } 

    if (myid == 0) {
// buffer, count, MPI_Datatype, source, tag, MPI_Comm
	MPI_Recv(receiveBuffer, msgsize, MPI_INT, 1, 2, MPI_COMM_WORLD, &status);
// buffer, count, MPI_Datatype, destination, tag, MPI_Comm
        printf("Rank %i received %i\n", myid, receiveBuffer[0]);
    } else if (myid == 1) {
	MPI_Send(message, msgsize, MPI_INT, 0, 2, MPI_COMM_WORLD);
        printf("Rank %i received %i\n", myid, receiveBuffer[0]);
    }

    free(message);
    free(receiveBuffer);
    MPI_Finalize();
    return 0;
}
