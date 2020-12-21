/* Example 3: Read 10 integers and print average, maximum and minimum of those numbers.*/

#include <stdio.h>
#include <limits.h>

int main() {

	int i, total = 0, maximum = INT_MIN, minimum = INT_MAX;
	float avg;

	for (i = 0; i < 10; i++) {
		int num;
		scanf("%d", &num);

		total += num;

		if (num > maximum)
			maximum = num;

		if (num < minimum)
			minimum = num;
	}

	avg = (float) total / 10.0;
	printf("Avg, Min, Max: %f %d %d\n", avg, minimum, maximum);

	return 0;
}
