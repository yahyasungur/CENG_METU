#include "the3.h"

using namespace std;

void countingSort(std::string arr[], int n, int l, int left, int &iter){
    iter++;
    string B[n];
    int pw1 = pow(26,l), pwe= 1;
    int cnvrtdvl;
    string temp;

    int count[pw1];


    for (int i = 0; i < pw1; i++){
        count[i] = 0;
        //iter++;
    }

    for (int i = 0; i < n; i++){
        iter++;
        cnvrtdvl = 0;
        temp = arr[i];

        for (int i2 = left; i2 < left+l; i2++){
            pwe =1;
            for (int j = 0; j < ((left+l)-i2-1); j++){
                pwe *= 26;
            }
            cnvrtdvl += pwe*((int)(temp[i2]-'A'));
        }
        count[cnvrtdvl] +=1;
    }

    for (int i = 1; i < pw1; i++){
        count[i] += count[i-1];
        iter++;
    }

    for (int i = n-1; i >= 0; i--){
        iter++;
        cnvrtdvl =0;
        temp = arr[i];

        for (int i2 = left; i2 < left+l; i2++){
            pwe =1;
            for (int j = 0; j < ((l+left)-i2-1); j++){
                pwe *=26;
            }
            cnvrtdvl += pwe*((int)(temp[i2]-'A'));
        }
        B[count[cnvrtdvl]-1] = arr[i];
        count[cnvrtdvl] -=1;
    }

    for (int i = 0; i < n; i++){
        iter++;
        arr[i] = B[i];
    }
}

int radixSort(std::string arr[], bool ascending, int n, int l){
    int iter = 0;
    if (n<=0){
        return 0;
    }

    int length = arr[0].length();
    int left = length%1;

    for (int i = length-l; i >= 0; i -=l){
        countingSort(arr,n,l,i,iter);
    }
    if (left != 0){
        countingSort(arr,n,left,0,iter);
    }
    if (!ascending){
        for (int i = 0; 2*i+2 <= n; i++){
            string temp = arr[i];
            arr[i] = arr[n-1-i];
            arr[n-1-i] = temp;
        }
        
    }

    return iter;
}


int main(){

    string array[] = {"AAA", "ABC", "ABA", "CCB"};
    int n = 4;
    int l = 1;
    bool ascending = true;

    int iter = radixSort(array,ascending,n,l);

    for (int i = 0; i < n; i++){
        cout << array[i] << " ";
    }
    printf("\n %d",iter);
    
    return 0;
}

