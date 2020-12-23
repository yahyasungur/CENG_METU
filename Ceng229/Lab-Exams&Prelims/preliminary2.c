#include <stdio.h>
#include <math.h>
int N,F,input_array[100][100],window_array[100][100],output_array[100][100];
void read(){
    int i,j;
    scanf(" %d %d",&N,&F);
    for (i=0;i<N;i++){
        for(j =0;j<N;j++){
        scanf(" %d",&input_array[i][j]);
        }
    }
}
void max_value(){
    int k,l,max =-1;
    static int a=0,b=0;
    for(k=0;k<F;k++){
        for(l=0;l<F;l++){
           if(window_array[k][l] > max){
               max = window_array[k][l];
           }
        }
    }   
    if(b != (N-F+1)){
        output_array[a][b] = max;
        b ++;
    }
    else{
        a++;
        b =0;
        if(b != (N-F+1)){
            output_array[a][b] = max;
            b ++;
        }
    }
}
void store_sort(){
    int i,j,k,l;
    for(i=0;i<N-F+1;i++){
        for(j=0;j<N-F+1;j++){
            for(k=0;k<F;k++){
                for(l=0;l<F;l++){
                    window_array[k][l] = input_array[k+i][l+j];
                }
            }
            max_value();
        }
    }
}
void write(){
    int i,j;
    for(i=0;i<N-F+1;i++){
        for(j=0;j<N-F+1;j++){
            printf("%d ",output_array[i][j]);
        }
        printf("\n");
    }
}
int main(){
    read();
    store_sort();
    write();
    return 0;
}