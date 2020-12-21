#include <stdio.h>

/* global variable declaration */
int a = 20;
int g = 40;

int sum(int, int);

int main () {

	/* local variable declaration in main function */
	int a = 10;
	int b = 20;
	int c = 0;

	printf ("value of a in main() = %d\n",  a);
	c = sum( a, b);
	printf ("value of c in main() = %d\n",  c);

	printf("value of g in main() = %d\n",  g);

	return 0;
}

/* function to add two integers */
int sum(int a, int b) {

	printf ("value of a in sum() = %d\n",  a);
	printf ("value of b in sum() = %d\n",  b);
	g = g + 20;

	return a + b;
}


