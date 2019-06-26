#include <stdio.h>

int main(int argc, char *argv[])
{
    int a, b, c;
    // declare a pointer variable and assign it to address of e.g. a
	int *p, *k;
	p = &a;
    // Evaluate expressions using both the original and the pointer variable
    // and investigate the value / value pointed to
	printf("address to a is %p \n", p);
	// %p is a pointer type
	// %ld shows pointer address as long integer
 	a = 10;
	printf("a has value %d and it's pointer is %p \n", a, p);
	
	a = (*p) + 2;
	printf("a has value %d and it's pointer is %p \n", a, p);
	
	b = a; 
	k = &b;
	printf("b has value %d and it's pointer is %p \n", b, k);

	b += 2;
	printf("b has value %d and it's pointer is %p \n", b, k);

	a = b;
	printf("a has value %d and it's pointer is %p \n", a, p);

    return 0;
}
