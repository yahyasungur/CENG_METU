#include <stdio.h>

int i = 0;

void f() {
	int i;
	i = 1;
}

void g() {
	i = 2;
}

void h(int i) {
	i = 3;
}

int main() {
	{
		int i = 4;
		printf("%d\n", i);
	}

	printf("%d\n", i);
	
	f();
	printf("%d\n", i);
	
	g();
	printf("%d\n", i);
	
	h(i);
	printf("%d\n", i);
	
	return 0;
}

