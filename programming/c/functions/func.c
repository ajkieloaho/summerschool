#include <stdio.h>

int add_one_to_both(int *a, int *b) {
	(*a) ++;
	(*b) ++;
	return 0;
}

int main(int argc, char *argv[]) {
	int a, b;
	a = 10;
	b = 20;
	add_one_to_both(&a, &b);

	printf("a is %d and b is %d\n", a, b);

	return 0;
}
