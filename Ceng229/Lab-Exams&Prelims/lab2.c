#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio.h>
float distanceMeasurer(int a, int b,float newlength, float newweight) {
	float distance = sqrt(pow((newlength - a), 2) + pow((newweight - b), 2));
	return distance;
}
struct fish {
	float length, weight, distance; int type, rank;
};
int main() {
	float newlength, newweight, min1;
	int rank,i,number,order1,order2,order3, order,seabass=0,salmon=0;
	struct fish fishs[5];
	scanf(" %d %f %f", &number, &newlength, &newweight);
	for ( i = 0; i < number; i++){
		scanf(" %f %f %d", &fishs[i].length, &fishs[i].weight, &fishs[i].type);
		fishs[i].distance = distanceMeasurer(fishs[i].length, fishs[i].weight, newlength, newweight);
		fishs[i].rank = 0;
	} 
	for ( rank = 0; rank < number; rank++){
		min1 = 300.0;
		for ( i = 0; i < number; i++){
			if (fishs[i].rank == 0 && fishs[i].distance < min1 ){
				min1 = fishs[i].distance;
				order = i;
			}
		}
		fishs[order].rank = rank + 1;
	}
	for (rank = 1; rank < 4; rank++) {
		for (i = 0; i < number; i++) if (fishs[i].rank == rank) fishs[i].type == 0 ? seabass++ : salmon++;
	}
	seabass < salmon ? printf("Salmon") : printf("Sea Bass");
	for (rank = 1; rank < 4; rank++) {
		for (i = 0; i < number; i++) if (fishs[i].rank == rank)printf("%.2f %.2f", fishs[i].length, fishs[i].weight);
	}

return 0;
}