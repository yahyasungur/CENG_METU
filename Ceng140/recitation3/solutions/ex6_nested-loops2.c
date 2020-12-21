/* Example 6: Find these triplets! */

#include <math.h>
#include <stdio.h>
#define LIMIT 25

int main(void) {

	int a, b, c, c_sqr;

	for (a = 1; a < LIMIT; a++) {
		for (b = a + 1; b <= LIMIT; b++) {
			c_sqr = a * a + b * b;
			c = sqrt(c_sqr);
			if (c * c == c_sqr)
				printf("%d %d %d\n", a, b, c);
		}
	}

	return 0;
}
