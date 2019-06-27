#include <stdio.h>

int main(int argc, char *argv[])
{
    // declare array and loop variable
    int f[20];
    int i;

    // initialize necessary array elements and write the for loop
	int f0, f1, f2;

	f0 = 0;
	f1 = 1;

	f[0] = f0;
	f[1] = f1;

	for (i = 2; i < 20; i++) {
		f2 = f1 + f0;

		f0 = f1;
		f1 = f2;
		f[i] = f2;
	}


    printf("First 20 Fibonacci numbers are:\n");
    for (i = 0; i < 20; i++) {
        printf("%d ", f[i]);
    }

    printf("\n");

    return 0;
}
