#include <stdio.h>
#include <stdlib.h>
#include "autopark_copy.h"

Car all_cars[100];


int main(){
    int* number_of_cars = malloc(sizeof(int));
    *number_of_cars = 0;

    register_car(all_cars, number_of_cars, "43 UD 117");
    
    /* This should print the plate */
    printf("%s\n", all_cars[0].plate);
    
    /* This should print -1 */
    printf("%d\n", find_car_slot_from_plate(all_cars, number_of_cars, "43 UD 116"));
    
    /* This should print 0 */
    printf("%d\n", find_car_slot_from_plate(all_cars, number_of_cars, "43 UD 117"));

    return 0;
}