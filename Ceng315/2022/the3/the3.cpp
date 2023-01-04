#include "the3.h"

int flag = 1;

int recursive_sln(int i, char**& arr, int*& len, int &number_of_calls) { //direct recursive
    number_of_calls+=1;
    if (i < 0) {
        return 0;
    }
    
    // if it is first call
    if (flag == 1){
        //int one = recursive_sln(i-1, arr, len, number_of_calls); // not use arr[i]
        flag = 0;
        int cals[i];
        for (int j = i-1; j >= 0; j--){
            cals[j] = recursive_sln(j, arr, len, number_of_calls);
        }
        int max = -1;
        for (int j = i-1; j >= 0; j--){
            if (cals[j] > max){
                max = cals[j];
            }
        }
        // use arr[i]
        char begin = arr[i][0];
        int j = i-1;
        while (j >= 0){
            if (begin == 'S' && arr[j][1] == 'S'){
                break;
            }
            else if (begin == 'I' && arr[j][1] == 'O'){
                break;
            }
            else if (begin == 'O' && arr[j][1] == 'I'){
                break;
            }
            j--;
        }
        int two;
        if (j < 0){
            two = len[i];
        }
        else{
            two = recursive_sln(j, arr, len, number_of_calls) + len[i];
        }
        return std::max(max, two);
    }
    // if this is not a first call
    else{
        // not use arr[i]
        char end = arr[i][1];
        int j = i-1;
        while (j >= 0){
            if (end == 'S' && arr[j][1] == 'S'){
                break;
            }
            else if (end == 'I' && arr[j][1] == 'I'){
                break;
            }
            else if (end == 'O' && arr[j][1] == 'O'){
                break;
            }
            j--;
        }
        int one;
        if (j < 0){
            one = 0;
        }
        else{
            one = recursive_sln(j, arr, len, number_of_calls);
        }
        // use arr[i]
        char begin = arr[i][0];
        j = i-1;
        while (j >= 0){
            if (begin == 'S' && arr[j][1] == 'S'){
                break;
            }
            else if (begin == 'I' && arr[j][1] == 'O'){
                break;
            }
            else if (begin == 'O' && arr[j][1] == 'I'){
                break;
            }
            j--;
        }
        int two;
        if (j < 0){
            two = len[i];
        }
        else{
            two = recursive_sln(j, arr, len, number_of_calls) + len[i];
        }
        return std::max(one, two);
    }
    // this is a dummy return value. YOU SHOULD CHANGE THIS!
}


int memory_index = 0;
int memoization_sln(int i, char**& arr, int*& len, int**& mem) { //memoization

    // if (i < 0) {
    //     //return 0;
    // }
    
    // // if it is first call
    // if (flag == 1){
    //     flag = 0;
    //     // not use arr[i]
    //     int cals[i];
    //     for (int j = i-1; j >= 0; j--){
    //         cals[j] = memoization_sln(j, arr, len, mem);
    //     }
    //     int max = -1;
    //     for (int j = i-1; j >= 0; j--){
    //         if (cals[j] > max){
    //             max = cals[j];
    //         }
    //     }
    //     // use arr[i]
    //     char begin = arr[i][0];
    //     int j = i-1;
    //     while (j >= 0){
    //         if (begin == 'S' && arr[j][1] == 'S'){
    //             break;
    //         }
    //         else if (begin == 'I' && arr[j][1] == 'O'){
    //             break;
    //         }
    //         else if (begin == 'O' && arr[j][1] == 'I'){
    //             break;
    //         }
    //         j--;
    //     }
    //     int two;
    //     if (j < 0){
    //         two = len[i];
    //     }
    //     else{
    //         two = memoization_sln(j, arr, len, mem) + len[i];
    //     }
    //     //return std::max(max, two);
    // }
    // // if this is not a first call
    // else{
    //     // not use arr[i]
    //     char end = arr[i][1];
    //     int j = i-1;
    //     while (j >= 0){
    //         if (end == 'S' && arr[j][1] == 'S'){
    //             break;
    //         }
    //         else if (end == 'I' && arr[j][1] == 'I'){
    //             break;
    //         }
    //         else if (end == 'O' && arr[j][1] == 'O'){
    //             break;
    //         }
    //         j--;
    //     }
    //     int one;
    //     if (j < 0){
    //         one = 0;
    //     }
    //     else{
    //         one = memoization_sln(j, arr, len, mem);
    //     }
    //     // use arr[i]
    //     char begin = arr[i][0];
    //     j = i-1;
    //     while (j >= 0){
    //         if (begin == 'S' && arr[j][1] == 'S'){
    //             break;
    //         }
    //         else if (begin == 'I' && arr[j][1] == 'O'){
    //             break;
    //         }
    //         else if (begin == 'O' && arr[j][1] == 'I'){
    //             break;
    //         }
    //         j--;
    //     }
    //     int two;
    //     if (j < 0){
    //         two = len[i];
    //     }
    //     else{
    //         two = memoization_sln(j, arr, len, mem) + len[i];
    //     }
    //     //return std::max(one, two);
    // }


    for (int index = i; index >= 0; index--){
        if ((i - index) > 0){
            mem[i-index][0] = mem[i-index-1][0];
            mem[i-index][1] = mem[i-index-1][1];
            mem[i-index][2] = mem[i-index-1][2];
        }
        else{
            mem[i-index][0] = 0;
            mem[i-index][1] = 0;
            mem[i-index][2] = 0;
        }

        if (arr[i-index][0] == 'S'){
            if ((arr[i-index][1] == 'S') && ((mem[i-index][2] + len[i-index]) > mem[i-index][2])){
                mem[i-index][2] = mem[i-index][2] + len[i-index];
            }
            else if((arr[i-index][1] == 'I') && ((mem[i-index][2] + len[i-index]) > mem[i-index][0])) { 
                mem[i-index][0] = mem[i-index][2] + len[i-index];
            }
            else if((arr[i-index][1] == 'O') && ((mem[i-index][2] + len[i-index]) > mem[i-index][1])) { 
                mem[i-index][1] = mem[i-index][2] + len[i-index];
            }
            
            // mem[i-index][2] += len[i-index];
        }
        else if (arr[i-index][0] == 'I'){
            if ((arr[i-index][1] == 'S') && ((mem[i-index][1] + len[i-index]) > mem[i-index][2])){
                mem[i-index][2] = mem[i-index][1] + len[i-index];
            }
            else if((arr[i-index][1] == 'I') && ((mem[i-index][1] + len[i-index]) > mem[i-index][0])) { 
                mem[i-index][0] = mem[i-index][1] + len[i-index];
            }
            else if((arr[i-index][1] == 'O') && ((mem[i-index][1] + len[i-index]) > mem[i-index][1])) { 
                mem[i-index][1] = mem[i-index][1] + len[i-index];
            }
            // mem[i-index][0] += len[i-index];
        }
        else if (arr[i-index][0] == 'O'){
            if ((arr[i-index][1] == 'S') && ((mem[i-index][0] + len[i-index]) > mem[i-index][2])){
                mem[i-index][2] = mem[i-index][0] + len[i-index];
            }
            else if((arr[i-index][1] == 'I') && ((mem[i-index][0] + len[i-index]) > mem[i-index][0])) { 
                mem[i-index][0] = mem[i-index][0] + len[i-index];
            }
            else if((arr[i-index][1] == 'O') && ((mem[i-index][0] + len[i-index]) > mem[i-index][1])) { 
                mem[i-index][1] = mem[i-index][0] + len[i-index];
            }
            // mem[i-index][1] += len[i-index];
        }
    }

    int max = 0;
    for (int k = 0; k < 3; k++){
        if (mem[i][k] > max){
            max = mem[i][k];
        }
    }
    
    return max; // this is a dummy return value. YOU SHOULD CHANGE THIS!
}



int dp_sln(int size, char**& arr, int*& len, int**& mem) { //dynamic programming

    //your code here
    int i = size-1;

    for (int index = i; index >= 0; index--){
        if ((i - index) > 0){
            mem[i-index][0] = mem[i-index-1][0];
            mem[i-index][1] = mem[i-index-1][1];
            mem[i-index][2] = mem[i-index-1][2];
        }
        else{
            mem[i-index][0] = 0;
            mem[i-index][1] = 0;
            mem[i-index][2] = 0;
        }

        if (arr[i-index][0] == 'S'){
            if ((arr[i-index][1] == 'S') && ((mem[i-index][2] + len[i-index]) > mem[i-index][2])){
                mem[i-index][2] = mem[i-index][2] + len[i-index];
            }
            else if((arr[i-index][1] == 'I') && ((mem[i-index][2] + len[i-index]) > mem[i-index][0])) { 
                mem[i-index][0] = mem[i-index][2] + len[i-index];
            }
            else if((arr[i-index][1] == 'O') && ((mem[i-index][2] + len[i-index]) > mem[i-index][1])) { 
                mem[i-index][1] = mem[i-index][2] + len[i-index];
            }
            
            // mem[i-index][2] += len[i-index];
        }
        else if (arr[i-index][0] == 'I'){
            if ((arr[i-index][1] == 'S') && ((mem[i-index][1] + len[i-index]) > mem[i-index][2])){
                mem[i-index][2] = mem[i-index][1] + len[i-index];
            }
            else if((arr[i-index][1] == 'I') && ((mem[i-index][1] + len[i-index]) > mem[i-index][0])) { 
                mem[i-index][0] = mem[i-index][1] + len[i-index];
            }
            else if((arr[i-index][1] == 'O') && ((mem[i-index][1] + len[i-index]) > mem[i-index][1])) { 
                mem[i-index][1] = mem[i-index][1] + len[i-index];
            }
            // mem[i-index][0] += len[i-index];
        }
        else if (arr[i-index][0] == 'O'){
            if ((arr[i-index][1] == 'S') && ((mem[i-index][0] + len[i-index]) > mem[i-index][2])){
                mem[i-index][2] = mem[i-index][0] + len[i-index];
            }
            else if((arr[i-index][1] == 'I') && ((mem[i-index][0] + len[i-index]) > mem[i-index][0])) { 
                mem[i-index][0] = mem[i-index][0] + len[i-index];
            }
            else if((arr[i-index][1] == 'O') && ((mem[i-index][0] + len[i-index]) > mem[i-index][1])) { 
                mem[i-index][1] = mem[i-index][0] + len[i-index];
            }
            // mem[i-index][1] += len[i-index];
        }
    }


    int max = 0;
    for (int k = 0; k < 3; k++){
        if (mem[i][k] > max){
            max = mem[i][k];
        }
    }
    
    return max;
}



// int main(){

//     char arr[3][2] = { {'I', 'S'}, {'O', 'I'}, {'S', 'O'} } ;
//     char **arr2 = new char*[3];
//     for (int i = 0; i < 3; i++){
//         arr2[i] = new char[2];
//         arr2[i][0] = arr[i][0];
//         arr2[i][1] = arr[i][1];
//     }
    
//     //int len[3] = { 1, 1, 1};
//     int * len = new int[3];
//     len[0] = 1;
//     len[1] = 1;
//     len[2] = 1;
//     int number_of_calls = 0;

//     std::cout<< "Length:" << recursive_sln(2,arr2,len,number_of_calls) << std::endl;
//     std::cout<< "Number of calls:" << number_of_calls << std::endl;

//     return 0;
// }