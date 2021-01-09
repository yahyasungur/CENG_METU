#include <stdio.h>
#include <stdlib.h>

struct complex
{
    /* x and y represents real and imaginary parts, respectively */
    float x, y;
};

struct complex *add(struct complex u, struct complex v)
{
    struct complex *z = (struct complex *)malloc(sizeof(struct complex));
    z->x = u.x + v.x;
    z->y = u.y + v.y;
    return z;
}

struct complex *subtract(struct complex u, struct complex v)
{
    struct complex *z = (struct complex *)malloc(sizeof(struct complex));
    z->x = u.x - v.x;
    z->y = u.y - v.y;
    return z;
}

struct complex *multiply(struct complex u, struct complex v)
{
    struct complex *z = (struct complex *)malloc(sizeof(struct complex));
    z->x = u.x * v.x - u.y * v.y;
    z->y = u.x * v.y + u.y * v.x;
    return z;
}

void readc(struct complex *u)
{
    scanf("%f %f", &u->x, &u->y);
}

void writec(struct complex *u)
{
    printf("(%f, %f)\n", u->x, u->y);
}

int main(void)
{
    struct complex z1, z2, z3;
    readc(&z1);
    readc(&z2);
    readc(&z3);
	
    printf("Addition:");
    writec(add(z1,z2));

    printf("Subtraction:");
    writec(subtract(z1,z3));
    
    printf("Multiplication:");
    writec(multiply(z2,z3));

    return 0;
}
