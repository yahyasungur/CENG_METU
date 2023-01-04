// #include "the4.h"

#include <iostream>
#include <climits>
#include <cmath>
#include <cstdlib>

int dp_sln(char**& arr1, char**& arr2, int nrow, int ncol1, int ncol2, int mem[4][4]){ //dynamic programming


    bool flag[ncol1+1][ncol2+1];
    for(int i = 0; i <= ncol1; i++)
        for(int j = 0; j <= ncol2; j++)
            flag[i][j] = false;

    // First row of memory array
    mem[0][0] = 0;
    for (int i = 0; i < ncol2; i++){
        int num = 0;
        for (int j = 0; j < nrow; j++){
            if (arr2[j][i] != '-'){
                num++;
            }
        }
        mem[0][i+1] = num + mem[0][i]; 
    }

    // First column of memory array
    for (int i = 0; i < ncol1; i++){
        int num = 0;
        for (int j = 0; j < nrow; j++){
            if (arr1[j][i] != '-'){
                num++;
            }
        }
        mem[i+1][0] = num + mem[i][0]; 
    }

    // Rest of the memory array
    for (int i = 1; i < ncol1+1; i++){ // iterate over rows
        for(int y = 0; y <= ncol1; y++)
            for(int z = 0; z <= ncol2; z++)
                flag[y][z] = false;


        int skip_array[nrow];
        for (int j = 0; j < nrow; j++){
            skip_array[j] = -1;
        }
        int skip_array_index = 0;
        for (int j = 1; j < ncol2+1; j++){ // iterate over columns
            int min = INT_MAX;
            int min_index = 0;
            for (int k = i-1; k <= i; k++){ // finds the min cost for constructing array untill the step j-1
                if (mem[k][j-1] < min){
                    bool skip_flag = false;
                    for (int p = 0; p < nrow; p++){
                        if (k == skip_array[p]){
                            skip_flag = true;
                            break;
                        }
                    }
                    if (skip_flag){
                        continue;
                    }
                    
                    min = mem[k][j-1];
                    min_index = k;
                }
                else if (mem[k][j-1] == min && flag[k][j-1] == true){
                    bool skip_flag = false;
                    for (int p = 0; p < nrow; p++){
                        if (k == skip_array[p]){
                            skip_flag = true;
                            break;
                        }
                    }
                    if (skip_flag){
                        continue;
                    }
                    min = mem[k][j-1];
                    min_index = k;
                }
            }
            // min = mem[i][j-1];
            char column1[nrow], column2[nrow];
            for (int k = 0; k < nrow; k++){
                column1[k] = arr1[k][i-1]; // construct the comparison column from box1
                column2[k] = arr2[k][j-1]; // construct the comparison column from box2
            }

            int cost_insert = 0, cost_reorder = 0, cost_replace = 0;

            // insertion cost
            for (int k = 0; k < nrow; k++){
                if (column2[k] != '-'){
                    cost_insert++;
                }
            }

            // reordering cost
            bool reorder_possible;
            for (int k = 0; k < nrow; k++){
                reorder_possible = false;
                for (int m = 0; m < nrow; m++){
                    if (column1[k] == column2[m] && column1[k] != '-'){
                        reorder_possible = true;
                        break;
                    }
                }
                if (!reorder_possible){
                    break;
                }
            }
            if (reorder_possible){
                for (int k = 0; k < nrow; k++){
                    if (column1[k] != column2[k]){
                        cost_reorder++;
                    }
                }
            }
            else{
                cost_reorder = INT_MAX;
            }

            // replacement cost
            for (int k = 0; k < nrow; k++){
                if (column1[k] != column2[k]){
                    cost_replace++;
                    if (column1[k] == '-' || column2[k] == '-'){
                        cost_replace++;
                    }
                }
            }
            
            int cost = 0;
            if (cost_insert < cost_reorder && cost_insert < cost_replace){
                cost = cost_insert;
            }
            else if (cost_reorder < cost_replace){
                cost = cost_reorder;
                flag[i][j] = true;
            }
            else{
                cost = cost_replace;
                flag[i][j] = true;
            }
            

            if (flag[min_index][j-1] == false && flag[i][j] == false){
                // deletion cost
                for (int k = 0; k < nrow; k++){
                    if (column1[k] != '-'){
                        cost_insert++;
                    }
                }
            }

            if (cost_insert < cost_reorder && cost_insert < cost_replace){
                cost = cost_insert;
            }
            else if (cost_reorder < cost_replace){
                cost = cost_reorder;
                flag[i][j] = true;
            }
            else{
                cost = cost_replace;
                flag[i][j] = true;
            }

            if (min + cost < mem[i][j-1]){
                skip_array[skip_array_index] = min_index;
                j--;
                skip_array_index++;
                flag[i][j] = false;
                continue;
            }
            
            mem[i][j] = min + cost;
            skip_array_index = 0;
            for (int p = 0;p < nrow; p++){
                skip_array[p] = -1;
            }
            
        }
    }

    return mem[ncol1][ncol2]; // this is a dummy return value. YOU SHOULD CHANGE THIS!
}


int main(){
    int nrow = 3;
    int ncol1 = 3;
    int ncol2 = 3;
    char **box1, **box2;

    box1 = new char* [nrow];
	box2 = new char* [nrow];
	
	for (int i = 0; i < nrow; i++) {
	   box1[i] = new char [ncol1];
	   box2[i] = new char [ncol2];
	}

    // "DO NOT FORGET TO CHANGE THE nrow, ncol1, ncol2 VALUES AT THE BEGINNING OF test() METHOD!!!!!!"	
	// EXAMPLE (a)
    
    box1[0][0] = 'D'; box1[0][1] = 'A'; box1[0][2] = 'D';
	box1[1][0] = '-'; box1[1][1] = 'D'; box1[1][2] = 'C';
	box1[2][0] = 'E'; box1[2][1] = '-'; box1[2][2] = 'E';
	
	box2[0][0] = 'A'; box2[0][1] = 'D'; box2[0][2] = '-';
	box2[1][0] = 'B'; box2[1][1] = 'B'; box2[1][2] = 'B';
	box2[2][0] = 'C'; box2[2][1] = 'B'; box2[2][2] = '-';


    // int** mem = new int*[ncol1+1];

    // for(int i = 0; i <= ncol1; i++){
	//     mem[i] = new int [ncol2+1];
	//     for (int j = 0; j <= ncol2; j++)
	// 	    mem[i][j] = -1;
	// }

    int mem[ncol1+1][4];

    for(int i = 0; i <= ncol1; i++){
        //mem[i] = new int [ncol2+1];
        for (int j = 0; j <= ncol2; j++)
    	    mem[i][j] = -1;
    }


    std::cout << dp_sln(box1, box2, nrow, ncol1, ncol2, mem) << std::endl;



    return 0;
}
