// #include "the2.h"
#include<stdio.h>

//You may write your own helper functions here

void swapp(unsigned short *arr, int index1, int index2){
    unsigned short temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;
}

int classical_partition(unsigned short *arr, int size, long &swap, double &avg_dist, double &max_dist){
    unsigned short x = arr[size-1];
    int i = -1;
    double temp_dist = 0;
    long initial_swap = swap;

    for(int j = 0; j <= size - 2; j++){ //Buradaki <= mi < mü kontrol et.
        if(arr[j] >= x){
            i++;
            swapp(arr, i , j);
            swap++;
            if(i > j){
                temp_dist += (i-j);
                if ((i-j) > max_dist){
                    max_dist = i-j;
                }
            }
            else{
                temp_dist += (j-i);
                if((j-i) > max_dist){
                    max_dist = j-i;
                }
            }
        }
    }
    swapp(arr, i+1, size-1);
    if(size-1 > i +1){
        temp_dist += (size-i-2);
    }
    else{
        temp_dist += (i-size+2);
    }
    if((size-i-2) > max_dist){ // ı am not sure if it should be there or not
        max_dist = size-i-2;
    }
    swap++;
    temp_dist = temp_dist/(double)(swap-initial_swap);
    avg_dist = (avg_dist*(double)initial_swap + temp_dist*(double)(swap-initial_swap))/(double)swap;
    return i+1;
}

int HOARE(unsigned short *arr, int size, long &swap, double &avg_dist, double &max_dist){
    unsigned short x = arr[(int)((size-1)/2)];
    int i = -1;
    int j = size;
    double temp_dist = 0;
    long initial_swap = swap;
    
    while (true){
        while (true){
            j--;
            if(arr[j] >= x){
                break;
            }
        }
        while (true){
            i++;
            if(arr[i] <= x ){
                break;
            }
        }

        if (i < j){
            swapp(arr,i,j);
            swap++;
            temp_dist += (j-i);
            if((j-i) > max_dist){
                max_dist = j-i;
            }
        }
        else{
            if (swap == 0 || swap == initial_swap){
                return j;
            }
            temp_dist = temp_dist/(double)(swap-initial_swap);
            avg_dist = (avg_dist*(double)initial_swap + temp_dist*(double)(swap-initial_swap))/(double)swap;
            return j;
        }
        
    }
    
}

void partition_3way(int &L, int &R, unsigned short *arr, long &swap, long &comparison, int size){
    int i = 0,j=0,p = size-1;
    int m;

    while (i < p){
        if (++comparison && arr[i] > arr[size -1]){
            swapp(arr, i ,j);
            swap++;
            i++;
            j++;
        }
        else if (++comparison && arr[i] == arr[size-1]){
            p--;
            swapp(arr, i ,p);
            swap++;
        }
        else{
            i++;
        }
    }
    if (p-j > size-p){
        m = size-p;
    }
    else{
        m = p-j;
    }

    for (int i = 0; i < m; i++){
        swapp(arr,j+i,size-m+i);
        swap++;
    }
    L = j;
    R = p-j;
}

void quickSort(unsigned short* arr, long &swap, double & avg_dist, double & max_dist, bool hoare, int size){

    if(hoare == false){
        if(size>1){
            int p = classical_partition(arr,size,swap,avg_dist,max_dist);
            quickSort(arr,swap,avg_dist,max_dist,false,p);
            quickSort(&arr[p+1],swap,avg_dist,max_dist,false,size-p-1);
        }
    }
    else{
        if (size>1){
            int p = HOARE(arr,size,swap,avg_dist,max_dist);
            quickSort(arr,swap,avg_dist,max_dist,true,p+1);
            quickSort(&arr[p+1],swap,avg_dist,max_dist,true,size-p-1);
        }
    }
}

void quickSort3(unsigned short *arr, long &swap, long &comparison, int size) {
	int L,R;
    if (size>1){
        partition_3way(L,R,arr,swap,comparison,size);
        quickSort3(arr,swap,comparison,L);
        quickSort3(&arr[size-R],swap,comparison,R);
    }
}


int main(){

    unsigned short array[] = {2, 1, 14, 6, 3, 0, 99, 3};
    int size = 8;
    long swap = 0;
    long comparison = 0;
    //double avg_dist = 0;
    //double max_dist = 0;

    //quickSort(array,swap,avg_dist,max_dist,true,size);
    quickSort3(array,swap,comparison,size);

    for(int i = 0; i < size; i++){
        printf(" %u",array[i]);
    }
    printf(" \n swap= %ld,  comparison= %ld   ",swap,comparison);

    return 0;
}