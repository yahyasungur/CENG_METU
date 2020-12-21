#include <math.h>
#include "the1_part1.h"

extern double global_mass;
extern double global_x;
extern double global_y;

void add_new_object(double center_x, double center_y, double mass) {
    
    global_x = (global_mass*global_x + mass*center_x)/(global_mass+mass);
    global_y = (global_mass*global_y + mass*center_y)/(global_mass+mass);
    global_mass += mass; 
 
}
