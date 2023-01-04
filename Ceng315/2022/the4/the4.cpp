#include "the4.h"
int dp_sln(char**& arr1, char**& arr2, int nrow, int ncol1, int ncol2, int**& mem){ //dynamic programming

    // First row of memory array
    mem[0][0]=0;
    for(int i=0;i<ncol2;i++){
        int num=0;
        for(int j=0;j<nrow;j++){
            if(arr2[j][i]!='-'){
                num++;
            }
        }
        mem[0][i+1]=mem[0][i]+num;
    }

    // First column of memory array
    for(int i=0;i<ncol1;i++){
        int num=0;
        for(int j=0;j<nrow;j++){
            if(arr1[j][i]!='-'){
                num++;
            }
        }
        mem[i+1][0]=mem[i][0]+num;
    }

    // Rest of the memory array
    for(int i=1;i < ncol1+1;i++){ // iterate over rows
        for(int j=1;j<=ncol2;j++){ // iterate over columns
            int cost = 0; 
            int cost_delete = 0;
            int cost_insert = 0;
            int cost_reorder;
            int cost_replace = 0;
            bool flag = true;

            // deletion cost
            for(int n = 0; n < nrow; n++){
                if(arr1[n][i-1] != '-'){
                    cost_delete++;
                }
            }

            // insertion cost
            for(int n = 0; n < nrow; n++){
                if(arr2[n][j-1] != '-'){
                    cost_insert++;
                }
            }

            // construct the columns of the both box1 and box2
            int column1[nrow], column2[nrow];
            for(int n=0;n<nrow;n++){
                column1[n]=arr1[n][i-1]; // column1 is the column of arr1 that we are comparing
                column2[n]=arr2[n][j-1]; // column2 is the column of arr2 that we are comparing
            }
            

            // A bubble sort algorithm to sort the column1, column2
            // Other sorting algorithms which have better time complexity can be used as well
            for (int a = 0; a < nrow - 1; a++){
                // Last i elements are already in place
                for (int b = 0; b < nrow - a - 1; b++) {
                    // If the element is not in the right order for column1, swap it
                    if (column1[b] > column1[b + 1]){
                        int temp = column1[b];
                        column1[b] = column1[b + 1];
                        column1[b + 1] = temp;
                    }
                    // If the element is not in the right order for column2, swap it
                    if (column2[b] > column2[b + 1]){
                        int temp = column2[b];
                        column2[b] = column2[b + 1];
                        column2[b + 1] = temp;
                    }
                }
            }

            // is the column1 and column2 are the same? If so, cost_reorder is 0
            // if they are not the same, then the cost_reorder is the number of elements that are not the same
            for(int n=0;n<nrow;n++){
                if(column1[n]!=column2[n]){
                    flag=false;
                }
            }      

            if(flag){
                cost_reorder = 0;
                for(int n = 0; n < nrow; n++){
                    if(arr1[n][i-1] != arr2[n][j-1]){
                        cost_reorder++;
                    }
                }
            }

            // replace cost
            for(int n = 0; n < nrow; n++){
                if(arr1[n][i-1] != arr2[n][j-1]){
                    if(arr1[n][i-1] == '-' || arr2[n][j-1] == '-'){
                        cost_replace+=2;
                    }
                    else{
                    cost_replace+=1;}
                }
            }
            
            cost = cost_replace;
            if(flag){
                if(cost_reorder < cost_replace){
                    cost = cost_reorder;
                }
            }

            // find the minimum cost
            int rep = mem[i-1][j-1] + cost,
                del = mem[i-1][j] + cost_delete,
                ins = mem[i][j-1] + cost_insert;

            if(del<rep) rep=del;
            if(ins<rep) rep=ins;
            mem[i][j] = rep;
        }
    }

    return mem[ncol1][ncol2]; 
}