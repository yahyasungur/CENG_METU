
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


char** split(char* str, char delimeter) {
	int i,j=0,k=0,start =0,g,h;
	char** store;
	store = (char**)malloc(1 * sizeof(char));

	for  (i = 0; *(str+i) != '\0' ; i++){
		if (str[i] == delimeter) {
			j++;
			store = (char**)realloc(store,j * sizeof(char));
			store[k] = (char*)malloc((i-start) * sizeof(char));
			
			if(start == 0) h=start;
			else h=start +1;
			
			for (g = 0; h < i; g++, h++) {
				*(*(store + k) + g) = str[h];
			}
			*(*(store + k) + (g + 1)) = '\0';
			k++;
			start = i;
		}
	}
	return store;
}


int main()
{
	int i;
	char** k;
	char arr[] = "ali, veli, kirk dokuz, elli altmis yetmis, sek sen,";
	char delimeter = ',';
	k = split(arr, delimeter);
	for (i = 0; *(k+i) != '\0'  ; i++){
		printf("%s\n", *(k + i));
	}
	
	
	
	return 0;

}
