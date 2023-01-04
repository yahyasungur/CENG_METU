#include "the2.h"
#include <cmath>
// You may write your own helper functions here

int returnMax(int *arr, int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

void countSort(int *arr, int n, int exp, long& numberOfIterations, int groupSize) {

    int output[n]; // output array
    int findingMaxArray[n];
    int divident = ((int)(pow(10, groupSize)));
    for (int i = 0; i < n; i++){
        findingMaxArray[i] = (arr[i] / exp) % divident;
    }
    int size = returnMax(findingMaxArray, n);
    int i, count[size] = {0};

    // Initialize count array with all zeros
    for (i = 0; i < size; i++){
        count[i] = 0;
        numberOfIterations++;
    }

    // Store count of occurrences in count[]
    for (i = 0; i < n; i++){
        count[ (arr[i]/exp) % divident ]++;
        numberOfIterations++;
    }

    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < size; i++){
        count[i] += count[i - 1];
        numberOfIterations++;
    }

    // Build the output array
    for (i = n - 1; i >= 0; i--){
        output[count[ (arr[i]/exp) % divident ] - 1] = arr[i];
        count[ (arr[i]/exp) % divident ]--;
        numberOfIterations++;
    }

    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

long multiDigitRadixSort(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength){
    long numberOfIterations = 0;
    
    for (int exp = 0, i = maxDigitLength; i > 0 ; i-=groupSize, exp*=(10*groupSize)){
        countSort(arr, arraySize, exp, numberOfIterations, groupSize);
    }

    return numberOfIterations;
}