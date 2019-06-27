#include <stdio.h>
#include <stdlib.h>

#define NX 258
#define NY 258

int main(void)
{
    int i, j;
    // Add here the definition for array with name 'array'
    // of size NX times NY (258x258)
// Define the array
// Allocate memory for pointer pointers
	double **array;
	array = malloc(NX * sizeof(float *));
// Allocate memory for data
	array[0] = malloc(NX * NY * sizeof(float));

// Point the beginning of each row at the correct address
	for (i = 0; i < NX; i++) {
		array[i] = array[0] + i * NY;
	}	

    // Initialize first the zeros
//#error Initialize the zeros for interior

	for (i = 1; i < NX-1; i++) {
		for (j = 1; j < NY-1; j++) {
			array[i][j] = 0.0;	
		}
	}

    // Initial conditions for left and right
//#error add boundary conditions for left and right
	for (i = 0; i < NX; i++) {
		array[i][0] = 20.0;
		array[i][NY-1] = 70.0;
	}
    // and top and bottom boundaries
//#error add boundary conditions for top and bottom
	for (j = 0; j < NY; j++) {
		array[0][j] = 85.0;
		array[NY-1][j] = 5.0;
	}
    return 0;
}
