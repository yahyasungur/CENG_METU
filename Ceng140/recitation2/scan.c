#include <stdio.h>

int main() {

    char c;
    int i;
    float f;
    double d;
    
    scanf("%c %d", &c, &i);
    
    printf("%c %d\n", c, i);
    
    scanf("%f %lf", &f, &d);
    
    printf("%f %f\n", f, d);
    

    return 0;
}
