#include <stdio.h>
#include <math.h>

int main() {
	int i, j, sum;
	sum=0;

	for (i=1; i<=100; i++){
		for (j=2; j <= sqrt(i); j++)
			if (i%j == 0)
				break;
		if (j>sqrt(i)){
			sum += i;
			printf("i = %d\n", i);
		}
	}

	printf("sum = %d\n", sum);

	return 0;
}
