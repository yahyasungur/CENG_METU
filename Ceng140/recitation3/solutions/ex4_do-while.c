/* Example 4: Determine the number of digits and their sum in a nonnegative decimal integer. */
#include <stdio.h>


int main(){

    int number, digits, sum;
    digits = sum = 0;
    scanf("%d", &number);

    do
    {
        sum += number % 10;
        number /= 10;
        digits++;
    } while(number > 0);

    printf("number of digits = %d sum = %d\n", digits, sum);

    return 0;
}