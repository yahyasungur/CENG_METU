#include <stdio.h>

int main() {

	int numbers[12] = {0, 5, 4, 2, 12, 125, 27, 10, 11, 23, 22, 17};
	int i, sum0 = 0, sum1 = 0, sum2 = 0;

	for (i = 0; i < 12; i++) {
		int a = numbers[i];
		switch (a % 3) {
			case 0:
				sum0 += a;
				break;
			case 1:
				sum1 += a;
				break;
			case 2:
				sum2 += a;
				break;
			default:
				break;
		}
	}

	printf("Sum 0: %d\n", sum0);
	printf("Sum 1: %d\n", sum1);
	printf("Sum 2: %d\n", sum2);

	return 0;
}
