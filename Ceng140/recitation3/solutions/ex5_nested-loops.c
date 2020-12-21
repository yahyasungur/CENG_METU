/* Draw a pyramide */

#include <stdio.h>

int main(){

	int size;
	int i,j;

	printf("Please enter the size of your pyramid:\n");
	scanf("%d",&size);

	for (i = 0; i <= size; i++) {
		for(j = 0; j < i; j++) {
			printf("#");
		}
		printf("\n");
	}


	return 0;
}