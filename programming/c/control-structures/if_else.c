#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 11;
    // write the control structure as described in the exercise
    // and run the code with different values for i

    if (i < 0) {
	    printf("i is negative\n");
    } else if (i == 0){
	    printf("i is zero\n");
    } else {
	    printf("i is positive\n");
    }

    return 0;
}
