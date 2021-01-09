#include<stdio.h>
#include<string.h>

#define MAX 50
void insertionsort (int array[], int size){
	int i,j;
	int element;
	
	for(i=1; i < size ;i++){
		element = array[i];
		j = i-1;
		while (j >= 0 && array[j] > element){
			array[j+1] = array[j];
			j--;
		}
		array[j+1] = element;
	}
}

int main () {
	int k,l;
	int array[MAX],size;
	printf("Lutfen Boyut Bilgisi Giriniz : ");
	scanf("%d",&size);
	for (k=0 ; k < size ; k++){
		printf("\nLutfen Arrayin %d. Terimini Giriniz : ",(k+1));
		scanf("%d",&array[k]);
	}
	
	insertionsort(array,size);
	
	for (l=0; l<size;l++){
		printf("%d  ",array[l]);
	}	
	
	
	getchar ();
	return 0;
}
