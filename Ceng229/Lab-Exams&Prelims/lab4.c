#include <stdio.h>
#include <math.h>
int F, N, input_array[100][100], window_array[100][100], output_array[100][100];
void read() {
	int i, j;
	scanf(" %d %d", &N, &F);
	for ( i = 0; i < N; i++){
		for ( j = 0; j < N; j++){
			scanf(" %d", &input_array[i][j]);
		}
	}
}
int maxfinder(int a) {
	int i, j,max =-100000;
	for ( i = 0; i < F; i++){
		for ( j = 0; j < F; j++){
			if (max < window_array[i][j]) max = window_array[i][j];
		}
	}
	return max;
}
void store() {
	int i, j,k,l;
	for ( i = 0; i < N-F+1; i++){
		for ( j = 0; j < N-F+1; j++){
			for ( k = 0; k < F; k++){
				for ( l = 0; l < F; l++){
					window_array[k][l] = input_array[k+i][l+j];
				}
			}
			output_array[i][j] = maxfinder(1);
		}
	}
}
void printfunction() {
	int i, j;
	for ( i = 0; i < N-F+1; i++){
		for ( j = 0; j < N-F+1; j++){
			printf("%d ", output_array[i][j]);
		}
		printf("\n");
	}
}
int main(){
	read();
	store();
	printfunction();
	return 0;
}