#include <stdio.h>
#ifdef _OPENACC
#include <openacc.h>
#endif

#define NX 102400

int main(void)
{
    double vecA[NX], vecB[NX], vecC[NX];
    double sum;
    int i;

    /* Initialization of the vectors */
    for (i = 0; i < NX; i++) {
        vecA[i] = 1.0 / ((double) (NX - i));
        vecB[i] = vecA[i] * vecA[i];
    }

    /* TODO:
     * Implement vector addition on device with OpenACC
     * vecC = vecA + vecB
     */

    sum = 0.0;
{
    #pragma acc kernels
    /* Compute the check value */
    for (i = 0; i < NX; i++) {
        vecC[i] = vecA[i] + vecB[i] ;
    }
}

    /* Compute the check value */
    for (i = 0; i < NX; i++) {
        sum += vecC[i];
    }
    printf("Reduction sum with kernels: %18.16f\n", sum);

    sum = 0.0;
{
    #pragma acc parallel loop
    /* Compute the check value */
    for (i = 0; i < NX; i++) {
        vecC[i] = vecA[i] + vecB[i] ;
    }
}

    /* Compute the check value */
    for (i = 0; i < NX; i++) {
        sum += vecC[i];
    }
    printf("Reduction sum with parallel: %18.16f\n", sum);
    return 0;
}
