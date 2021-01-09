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
	float length, weight, distance; int type;
};
int main() {
	float newlength, newweight, min1 = 300.0,min2 = 300.0,min3 = 300.0;
	int rank,i,number,order1,order2,order3, order,seabass=0,salmon=0;
	struct fish fishs[5];
	scanf(" %d %f %f", &number, &newlength, &newweight);
	for ( i = 0; i < number; i++){
		scanf(" %f %f %d", &fishs[i].length, &fishs[i].weight, &fishs[i].type);
		fishs[i].distance = distanceMeasurer(fishs[i].length, fishs[i].weight, newlength, newweight);
	} 
	for (i = 0; i < number; i++) if (fishs[i].distance < min1) { min1 = fishs[i].distance; order1 = i; }
	fishs[order1].type == 0 ? seabass++: salmon++;
	for (i = 0; i < number; i++) if (fishs[i].distance < min2 && fishs[i].distance > min1) { min2 = fishs[i].distance; order2 = i; }
	fishs[order2].type == 0 ? seabass++: salmon++;
	for (i = 0; i < number; i++) if (fishs[i].distance < min3 && fishs[i].distance > min2) { min3 = fishs[i].distance; order3 = i; }
	fishs[order3].type == 0 ? seabass++: salmon++;
	salmon > seabass ? printf("Salmon\n"): printf("Sea Bass\n");
	printf("%.2f %.2f\n", fishs[order1].length, fishs[order1].weight);
	printf("%.2f %.2f\n", fishs[order2].length, fishs[order2].weight);
	printf("%.2f %.2f\n", fishs[order3].length, fishs[order3].weight);
	return(0);
}