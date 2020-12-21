#include <stdio.h>
#include <math.h>
#include "the1_part2.h"

int main(){

    int i,j;
    int layer;
    long double weight,press;
    
    scanf(" %d %Lf",&layer,&weight);
    
    /* i represents y-axis (row), j represents x-axis (column) */
    for (i = 0; i < layer; i++){
        for ( j = 0; j <= i; j++){
            press = calculate_pressure_on_block(i,j,weight);
            printf("(%d,%d) -> %.8Lf\n",i,j,press);
        }   
    }

    return 0;
}