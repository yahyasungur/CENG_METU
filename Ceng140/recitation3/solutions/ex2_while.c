/* Example 2: Take two integers as input and print the greatest common divisor of them.*/

#include <stdio.h>

int main() {

	int a, b;

	printf("Enter two integers: ");
	scanf("%d %d", &a, &b);

	while (a != b) {

		if (a > b) {
			a -= b;
		}
		else {
			b -= a;
		}
	}

	printf("%d\n", a);

	return 0;
}
