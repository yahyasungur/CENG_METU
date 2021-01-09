#include <stdlib.h>
#include <string.h>
#include "autopark_copy.h"

void register_car(Car *all_cars, int* number_of_cars, char* plate) {
    (*number_of_cars)++;
    all_cars[(*number_of_cars)-1].plate = plate;
}

int find_car_slot_from_plate(Car *all_cars, int* number_of_cars, char *plate) {
    int i;
    for ( i = 0; i < *(number_of_cars); i++){
        if (strcmp(all_cars[i].plate,plate) == 0){
            return i;
        }
    }
    return -1;
}