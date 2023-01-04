#include "the0.h"

void insertionSort(int* arr, long &comparison, long & swap, int size) {
    int i = 1;
    int x;
    while (i < size){
        x = arr[i];
        int j = i - 1;
        comparison++;
        while (j >= 0 && arr[j] > x){
            arr[j + 1] = arr[j];
            j--;
            comparison++;
            swap++;
        }
        arr[j + 1] = x;
        i++;
    }
}