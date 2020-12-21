#include <stdio.h>
#include "lab_2_0_copy.h"

/* TASK SOLUTIONS */

void is_it_zero(int *arr,int length){
	int i,num_zero = 0,sum =0;
	static int k = 0;
	if (k == 0){
		printf("{}\n");
		k++;
	}
	
	for ( i = 0; i < length; i++){
		sum += arr[i];
		if (arr[i] == 0){
			num_zero++;
		}
		
	}

	if (num_zero != length){
		if (sum == 0){
			printf("{");
			for ( i = 0; i < length; i++){
				if (arr[i] != 0){
				printf("%d ",arr[i]);
				}
			}
			printf("}\n");
		}
	}
}

void sum_zero_subsets_helper(int *array,int len, int index){
	int i;
	int arr[50];

	for ( i = 0; i < len; i++){
		arr[i] = array[i];
	}

	if (index == len){
		is_it_zero(arr,len);
		return;
	}
	sum_zero_subsets_helper(arr,len,index+1);
	*(arr+index) = 0;
	sum_zero_subsets_helper(arr,len,index+1);

}

void sum_zero_subsets(int *numbers, int len) {
	sum_zero_subsets_helper(numbers,len,0);
	
	/* TODO: Implement this function */
}