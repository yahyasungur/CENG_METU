#include "stdlib.h"
#include "helper.h"

char *convert_to_char_array(long int num, int *len)
{
    int digit_count = 0, i;
    long int temp = num;
    char *str;

    while (temp != 0)
    {
        digit_count++;
        temp /= 10;
    }
    *len = digit_count;

    str = (char *)malloc(sizeof(char) * digit_count);

    for (i = digit_count - 1; i >= 0; i--)
    {
        str[i] = (num % 10) + '0';
        num /= 10;
    }

    return str;
}