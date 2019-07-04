/* Main solver routines for heat equation solver */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <mpi.h>
#include <omp.h>
#include "heat.h"

/* Exchange the boundary values */
void exchange(field *temperature, parallel_data *parallel)
{

    int tid, length;
#pragma omp parallel private(tid)
{ // start of parallel region

    tid = omp_get_thread_num();

    length = parallel->displacements[tid + 1] 
	- parallel->displacements[tid];


    /* TODO start: implement halo exchange */
    // Send to the up, receive from down
    MPI_Isend(
	&temperature->data[1][parallel->displacements[tid]],
	//temperature->ny + 2, MPI_DOUBLE,
	length, MPI_DOUBLE,
	parallel->nup, 1,
	parallel->communicators[tid], &parallel->requests[0]
    );

    MPI_Irecv(
	&temperature->data[temperature->nx + 1][parallel->displacements[tid]],
	//temperature->ny + 2, MPI_DOUBLE, 
	length, MPI_DOUBLE,
	parallel->ndown, 1,
	parallel->communicators[tid], &parallel->requests[1] 
    );

    // Send to the down, receive from up
    MPI_Isend(
	&temperature->data[temperature->nx][parallel->displacements[tid]],
	//temperature->ny + 2, MPI_DOUBLE,
	length, MPI_DOUBLE,
	parallel->ndown, 2,
	parallel->communicators[tid], &parallel->requests[2]
    );
    
    MPI_Irecv(
	&temperature->data[0][parallel->displacements[tid]],
	//temperature->ny + 2, MPI_DOUBLE, 
	length, MPI_DOUBLE,
	parallel->nup, 2,
	parallel->communicators[tid], &parallel->requests[3]
    );
 } // End of parallel region   

   MPI_Waitall(4, parallel->requests, MPI_STATUS_IGNORE);
}


/* Update the temperature values using five-point stencil */
void evolve(field *curr, field *prev, double a, double dt)
{
    int i, j;
    double dx2, dy2;

    /* Determine the temperature field at next time step
     * As we have fixed boundary conditions, the outermost gridpoints
     * are not updated. */
    dx2 = prev->dx * prev->dx;
    dy2 = prev->dy * prev->dy;

#pragma omp parallel shared(curr, prev), private(i, j)
{
    #pragma omp for schedule(guided)
    for (i = 1; i < curr->nx + 1; i++) {
        for (j = 1; j < curr->ny + 1; j++) {
            curr->data[i][j] = prev->data[i][j] + a * dt *
                               ((prev->data[i + 1][j] -
                                 2.0 * prev->data[i][j] +
                                 prev->data[i - 1][j]) / dx2 +
                                (prev->data[i][j + 1] -
                                 2.0 * prev->data[i][j] +
                                 prev->data[i][j - 1]) / dy2);
}
        }
    }
}


