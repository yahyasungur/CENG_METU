#include <stdio.h>



void reverse(int * arr[], int length){
    
    int i;
    int *temp;
    for ( i = 0; i < length/2; i++){
        
        temp = *(arr + length-i-1);
        *(arr + length-i-1) = *(arr + i);
        *(arr + i) = temp;
    }
}




int main(){

int arr[5] = {1,2,3,4,5};
int *ptrs[5], i=0;

for(i=0; i < 5; i++) /* DO NOT CHANGE */
    ptrs[i] = arr+i;

reverse(ptrs, 5); /* try your function here */

for(i=0; i < 5; i++)  /* DO NOT CHANGE */
    printf("%d ", *ptrs[i]);

return 0;
}