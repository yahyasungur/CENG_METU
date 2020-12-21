#include <stdio.h>

int increment(int var)
{
    var = var+1;
    return var;
}

int main()
{
   int num1=20;
   int num2 = increment(num1);
   printf("num1 value is: %d\n", num1);
   printf("num2 value is: %d\n", num2);

   return 0;
}