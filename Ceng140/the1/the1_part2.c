#include <math.h>
#include "the1_part2.h"

double calculate_pressure_on_block(int row, int column, double block_weight){

    long double press;

    if (row == 0){
        press = 0.0;
    }
    else if(column != row && column != 0){
        press = block_weight + calculate_pressure_on_block(row-1,column-1,block_weight)*0.15 + calculate_pressure_on_block(row-1,column,block_weight)*0.15 ;
    }
    else if (column == 0){
        press = block_weight*0.5 + calculate_pressure_on_block(row-1,column,block_weight)*0.15;
    }
    else if (column == row){
        press = block_weight*0.5 + calculate_pressure_on_block(row-1,column-1,block_weight)*0.15;
    }

   return press;
}
