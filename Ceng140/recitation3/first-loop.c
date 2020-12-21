#include <stdio.h>

int main() {
    int i, n;
    float sum;
    scanf("%d", &n);
    i = 1, sum = 0;
    while (i <= n) {
        sum += 1.0/ i;
        i++;
    }
    printf("sum = %f\n", sum);
    return 0;
}