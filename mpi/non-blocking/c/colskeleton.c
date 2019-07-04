#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define NTASKS 4

void print_buffers(int *printbuffer, int *sendbuffer, int buffersize);
void init_buffers(int *sendbuffer, int *recvbuffer, int buffersize);


int main(int argc, char *argv[])
{
    int ntasks, rank;
    int sendbuf[2 * NTASKS], recvbuf[2 * NTASKS];
    int printbuf[2 * NTASKS * NTASKS];
    int displs[4], rcvcounts[4];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Request request;
    MPI_Status status;

    if (ntasks != NTASKS) {
        if (rank == 0) {
            fprintf(stderr, "Run this program with %i tasks.\n", NTASKS);
        }
        MPI_Abort(MPI_COMM_WORLD, -1);
    }

    /* Initialize message buffers */
    init_buffers(sendbuf, recvbuf, 2 * NTASKS);

    /* Print data that will be sent */
    print_buffers(printbuf, sendbuf, 2 * NTASKS);

    /* TODO: use a single collective communication call (and maybe prepare
     *       some parameters for the call) */
//    MPI_Bcast(sendbuf, 8, MPI_INT, 0, MPI_COMM_WORLD);
//    MPI_Scatter(sendbuf, 2, MPI_INT, 
//	recvbuf, 2, MPI_INT, 0, MPI_COMM_WORLD);

//    rcvcounts[0] = 1; rcvcounts[1] = 1; rcvcounts[2] = 2; rcvcounts[3] = 4;
//    displs[0] = 0; displs[1] = 1; displs[2] = 2; displs[3] = 4;
//    MPI_Gatherv(sendbuf, rcvcounts[rank], MPI_INT, recvbuf, rcvcounts, displs, MPI_INT, 1, MPI_COMM_WORLD);

    MPI_Ialltoall(sendbuf, 2, MPI_INT, recvbuf, 2, MPI_INT, MPI_COMM_WORLD, &request);
    MPI_Wait(&request, &status);
    /* Print data that was received */
    /* TODO: add correct buffer */
//    print_buffers(printbuf, sendbuf, 2 * NTASKS);
    print_buffers(printbuf, recvbuf, 2 * NTASKS);
    MPI_Finalize();
    return 0;
}


void init_buffers(int *sendbuffer, int *recvbuffer, int buffersize)
{
    int rank, i;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    for (i = 0; i < buffersize; i++) {
        recvbuffer[i] = -1;
        sendbuffer[i] = i + buffersize * rank;
    }
}


void print_buffers(int *printbuffer, int *sendbuffer, int buffersize)
{
    int i, j, rank, ntasks;

    MPI_Gather(sendbuffer, buffersize, MPI_INT,
               printbuffer, buffersize, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);

    if (rank == 0) {
        for (j = 0; j < ntasks; j++) {
            printf("Task %i:", j);
            for (i = 0; i < buffersize; i++) {
                printf(" %2i", printbuffer[i + buffersize * j]);
            }
            printf("\n");
        }
        printf("\n");
    }
}