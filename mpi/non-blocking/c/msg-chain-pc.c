#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
    int i, myid, ntasks, destination, source;
    int msgsize = 10000000;
    int *message;
    int *receiveBuffer;
    MPI_Status statuses[2];
    MPI_Request requests[2];
    double t0, t1;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    /* Allocate message buffers */
    message = (int *)malloc(sizeof(int) * msgsize);
    receiveBuffer = (int *)malloc(sizeof(int) * msgsize);
    /* Initialize message */
    for (i = 0; i < msgsize; i++) {
        message[i] = myid;
    }

    /* Start measuring the time spent in communication */
    MPI_Barrier(MPI_COMM_WORLD);
    t0 = MPI_Wtime();

    /* TODO start */
    /* Send and receive messages as defined in exercise */

    if (myid < ntasks - 1) {
	destination = myid + 1;
    } else {
	destination = MPI_PROC_NULL;
    }

    if (myid > 0) {
	source = myid - 1;
    } else {
	source = MPI_PROC_NULL;
    }

//    MPI_Sendrecv(message, msgsize, MPI_INT, destination, destination,
//	receiveBuffer, msgsize, MPI_INT, source, destination,
//	MPI_COMM_WORLD, &status);

//    MPI_Sendrecv(message, msgsize, MPI_INT, destination, destination,
//	receiveBuffer, msgsize, MPI_INT, source, destination,
//	MPI_COMM_WORLD, &status);

// There is no need for even/odd send-receive, 'cuz this is acyclic
    MPI_Isend(message, msgsize, MPI_INT, destination, myid + 1, MPI_COMM_WORLD, &requests[1]);
    MPI_Irecv(receiveBuffer, msgsize, MPI_INT, source, MPI_ANY_TAG, MPI_COMM_WORLD, &requests[0]);
    MPI_Waitall(2, requests, statuses);

    printf("Sender: %d. Sent elements: %d. Tag: %d. Receiver: %d\n",
               myid, msgsize, myid + 1, myid + 1);

    printf("Receiver: %d. first element %d.\n",
               myid, receiveBuffer[0]);

    /* TODO end */

    /* Finalize measuring the time and print it out */
    t1 = MPI_Wtime();
    MPI_Barrier(MPI_COMM_WORLD);
    fflush(stdout);

    printf("Time elapsed in rank %2d: %6.3f\n", myid, t1 - t0);

    free(message);
    free(receiveBuffer);
    MPI_Finalize();
    return 0;
}
