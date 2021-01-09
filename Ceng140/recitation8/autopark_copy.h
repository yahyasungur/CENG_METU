#ifndef AUTOPARK_H
#define AUTOPARK_H

struct MyCar {
    char* plate;
};

typedef struct MyCar Car;

void register_car(Car *all_cars, int* number_of_cars, char* plate);
int find_car_slot_from_plate(Car *all_cars, int* number_of_cars, char *plate);

#endif