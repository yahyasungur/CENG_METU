#include <stdio.h>

int main() {

    int c, vowel, vowelcount, charcount;
    vowelcount = charcount = 0;

    /* c = 'A';
     printf("A: %d\n", c);
     c = 'Z';
     printf("Z: %d\n", c);
     c = 'a';
     printf("a: %d\n", c);
     c = 'z';
     printf("z: %d\n", c); */

    while ((c = getchar()) != EOF) {

        c = (c >= 'A' && c <= 'Z') ? (c - 'A' + 'a') : c;
        vowel = c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
        if (vowel) vowelcount++;
        charcount++;
    }

    printf("vowels = %f\n", (float)vowelcount/charcount);

	return 0;
}
