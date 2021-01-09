//#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio.h>
int main() {
	int i, number, seabass = 0, salmon = 0, min1 = 0, min2 = 0, min3 = 0;
	float length[100], distance[100];
	float weight[100];
	float newlength, newweight, temporary, min1distance = 300.00, min2distance = 300.00, min3distance = 300.00;
	int type[100];
	scanf(" %d", &number);
	scanf(" %f %f", &newlength, &newweight);

	for (i = 0; i < number; i++) {
		scanf(" %f %f %d", &length[i], &weight[i], &type[i]);
	}
	for (i = 0; i < number; i++) {
		distance[i] = (float)sqrt((newlength - length[i]) * (newlength - length[i]) + (newweight - weight[i]) * (newweight - weight[i]));
	}
	for (i = 0; i < number; i++) {
		if (distance[i] < min1distance) {
			min1distance = distance[i];
			min1 = i;
		}}
	for (i = 0; i < number; i++) {
		if (distance[i] < min2distance && distance[i] > min1distance) {
			min2distance = distance[i];
			min2 = i;
		}}
	for (i = 0; i < number; i++) {
		if (distance[i] < min3distance && distance[i] > min2distance&& distance[i] > min1distance) {
			min3distance = distance[i];
			min3 = i;
		}}
	if (type[min1] == 0) seabass++;
	else salmon++;
	if (type[min2] == 0) seabass++;
	else salmon++;
	if (type[min3] == 0) seabass++;
	else salmon++;
	if (salmon > seabass) printf("Salmon\n");
	else printf("Sea Bass\n");
	
	printf("%.2f %.2f\n", length[min1], weight[min1]);
	printf("%.2f %.2f\n", length[min2], weight[min2]);
	printf("%.2f %.2f\n", length[min3], weight[min3]);
	return(0);
}