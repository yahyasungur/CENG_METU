//#include "the0.h"
#include<stdio.h>

void insertionSort(int* arr, long &comparison, long & swap, int size){

    int i = 1,k;
    int lenth = size;
    int x;
    int j;

    while (i < lenth){
        x = arr[i];
        j = i-1;

        while (j >= 0 && ++comparison && arr[j] > x){
            arr[j+1] = arr[j];
            swap++;
            j--;

        }
        arr[j+1] = x;
        i++;
    }
    
    printf("Comparison: %ld, Swap: %ld \n",comparison,swap);
    for(k=0 ; k<lenth; k++){
        printf("%d ",arr[k]);
    }
    //Your Code Here
    
}

int main(){

    int array[] = {0, -5, -5, -5, 4, 1};
    long comp = 0, sw = 0;

    insertionSort(array,comp,sw,6);

    return 0;
}