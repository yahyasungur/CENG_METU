// #include "the4.h"
#include<iostream>
#include<climits>
#include<cmath>
#include<cstdlib>



int recursive_sln(int i, int*& arr, int &number_of_calls){ //direct recursive
    number_of_calls+=1;

    //your code here

    return 0; // this is a dummy return value. YOU SHOULD CHANGE THIS!
}



int memoization_sln(int i, int* arr, int* mem){ //memoization
    int max = arr[0];

    for (int j = 0; j < i+1; j++){
        if(j < 3){
            if (max < arr[j]){
                max = arr[j];
            }
        }
        for (int k = 0; k <= j-3; k++){
            if (max < mem[j] + arr[k]){
                max = mem[j] + arr[k];
            }
        }
        mem[j] = max;
    }

    return max; // this is a dummy return value. YOU SHOULD CHANGE THIS!
}



int dp_sln(int size, int*& arr, int*& mem){ //dynamic programming

    //your code here

    return 0; // this is a dummy return value. YOU SHOULD CHANGE THIS!
}

int main(){

    int arr[] = {32, 51, 51, 92, 54, 90, 13, 69, 20, 6};
    int i = 9;
    int mem[i+1];

    int result = memoization_sln(i,arr,mem);

    std::cout << "\n";
    std::cout << result;
    std::cout <<"\n{ ";
    for (int j = 0; j < i+1; j++){
        printf(" %d",mem[j]);
    }
    std::cout << "}\n\n";



    return 0;
}