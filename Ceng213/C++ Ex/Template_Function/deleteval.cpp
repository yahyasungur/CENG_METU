#include <iostream>

// Write a C++ template function to solve the following problem: 
// delete a value val from an unsorted array A[0..n-1]. Assume all values 
// in A are distinct. 
// Use the following function header:
template<class C>
void delete_val(C A[], int &n, C val);
// n is the number of elements in the array, val is the value to be deleted
// n must be decreased by one if deletion is successful

// First find the location of val in the array.
// Delete val by shifting the remaining elements to the left by one position.
// Decrement n.
template<class C>
void delete_val(C A[], int &n, C val)
{   
    int i;
    for (i = 0; i < n; i++){
        if (A[i] == val){
            break;
        }
    }
    for (; i < n; i++){
        A[i] = A[i+1];
    }
    n--;
    // TODO
}


