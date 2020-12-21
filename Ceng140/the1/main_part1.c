#include <stdio.h>
#include <math.h>
#include "the1_part1.h"

double global_mass = 0, global_x = 0, global_y = 0;

int main()
{
    int i,j;
    int number_of_objects;
    long double x,y,m,center_x,center_y;
    char shape;

    scanf(" %d",&number_of_objects);
    
    for ( i = 0; i < number_of_objects; i++){
        scanf(" %c %Lf",&shape,&m);
        center_x = 0.0;
        center_y = 0.0;
        switch (shape){
        case 'L' :
            for ( j = 0; j < 2; j++){
                scanf(" %Lf %Lf",&x,&y);
                center_x += x;
                center_y += y;
            }
            center_x /= j;
            center_y /= j;    
            break;

        case 'T' :
            for ( j = 0; j < 3; j++){
                scanf(" %Lf %Lf",&x,&y);
                center_x += x;
                center_y += y;
            }
            center_x /= j;
            center_y /= j; 
            break;

        case 'R' :
            for ( j = 0; j < 4; j++){
                scanf(" %Lf %Lf",&x,&y);
                center_x += x;
                center_y += y;
            }
            center_x /= j;
            center_y /= j;             
            break;

        case 'P' :
            for ( j = 0; j < 5; j++){
                scanf(" %Lf %Lf",&x,&y);
                center_x += x;
                center_y += y;
            }
            center_x /= j;
            center_y /= j;             
            break;

        case 'H' :
            for ( j = 0; j < 6; j++){
                scanf(" %Lf %Lf",&x,&y);
                center_x += x;
                center_y += y;
            }
            center_x /= j;
            center_y /= j;             
            break;

        default:
            break;
        }        
        add_new_object(center_x,center_y,m);
    }

    printf("X: %f Y: %f Total Mass: %f\n", global_x, global_y, global_mass);

    return 0;
}