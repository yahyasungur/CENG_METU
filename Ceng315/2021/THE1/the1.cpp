//#include "the1.h"
#include<stdio.h>


//You can add your own helper functions

void swapp(int *arr,int index1, int index2){
	int temp = arr[index1];
	arr[index1] = arr[index2];
	arr[index2] = temp;
}

void merge(int h1[],int *arr1, int *arr2,int size, long &comparison){
		int i=0,j=0,k=0;

		while (i < size && j < size){
			if(arr1[i] < arr2[j]){
				h1[k] = arr1[i];
				i++;
			}
			else{
				h1[k] = arr2[j];
				j++;
			}
			k++;
			comparison++;
		}
		while (i < size){
			h1[k] = arr1[i];
			i++;
			k++;
		}
		while (j < size){
			h1[k] = arr2[j];
			j++;
			k++;
		}
}

int sillySort(int* arr, long &comparison, long & swap, int size){

    int num_of_calls=1;
	int first,second,third,fourth,fifth,sixth;

	if (size == 0 || size == 1){
		return num_of_calls;
	}
	else if(size == 2){
		if (arr[0] > arr[1]){
			swapp(arr,0,1);
			swap++;
		}
		comparison++;
		return num_of_calls;
	}
	else if(size == 3){
		if (arr[0] > arr[1]){
			swapp(arr,0,1);
			swap++;
		}
		comparison++;
		if (arr[1] > arr[2]){
			swapp(arr,1,2);
			swap++;
		}
		comparison++;
		if (arr[0] > arr[1]){
			swapp(arr,0,1);
			swap++;
		}
		comparison++;

		return num_of_calls;
	}
	else{
		first = sillySort(arr,comparison,swap,size/2);
		second = sillySort(&arr[size/4],comparison,swap,size/2);
		third = sillySort(&arr[size/2],comparison,swap,size/2);
		fourth = sillySort(arr,comparison,swap,size/2);
		fifth = sillySort(&arr[size/4],comparison,swap,size/2);
		sixth = sillySort(arr,comparison,swap,size/2);
		return 1 + first + second + third + fourth + fifth + sixth;
	}
}


int crossMergeSort(int *arr, long &comparison, int size){

	int num_of_calls=1;
	int first,second,third,fourth;

	if(size == 1){
		return num_of_calls;
	}
	else if (size == 2){
		if(arr[0] > arr[1]){
			swapp(arr,0,1);
		}
		comparison++;
		return num_of_calls;
	}
	else{
		first = crossMergeSort(arr,comparison,size/4);
		second = crossMergeSort(&arr[size/4],comparison,size/4);
		third = crossMergeSort(&arr[size/2],comparison,size/4);
		fourth = crossMergeSort(&arr[3*size/4],comparison,size/4);

		int h1[size/2];
		int h2[size/2];

		merge(h1,arr,&arr[size/2],size/4,comparison);
		merge(h2,&arr[size/4],&arr[3*size/4],size/4,comparison);
		merge(arr,h1,h2,size/2,comparison);

		return 1 + first + second + third + fourth;
	}
/*
		while (i < size/4 && j < size/4){
			if(arr[i] < arr[size/2 + j]){
				h1[k] = arr[i];
				i++;
			}
			else{
				h1[k] = arr[size/2 + j];
				j++;
			}
			k++;
			comparison++;
		}
		while (i < size/4){
			h1[k] = arr[i];
			i++;
			k++;
		}
		while (j < size/4){
			h1[k] = arr[size/2 + j];
			j++;
			k++;
		}
		
		
*/
	
}



int main(){
	int i;
	int numberofcalls = 0;

	int arr[] = {0, -5, 2, 6, 4, 18, 22, -14};
	int size = 8;

	long comparison = 0;

	numberofcalls = crossMergeSort(arr,comparison,size);

	printf("\nsorted array = {");
	for(i = 0; i < size; i++){
		printf(" %d",arr[i]);
	}
	printf(" } \nnumber_of_calls = %d , comparison = %ld \n",numberofcalls,comparison);

	return 0;
}