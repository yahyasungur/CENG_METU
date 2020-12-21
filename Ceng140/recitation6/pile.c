#include <stdio.h>
#include <stdlib.h>

char* pile(char* str1, char* str2) {
    char *result;
    int i=0,j=0,k=0;
    int len_1,len_2;

    while (str1[i] != '\0'){
        i++;
    }
    len_1 = i;
    while (str2[j] != '\0'){
        j++;
    }
    len_2 = j;
    result = (char*)malloc((len_1+len_2+1)*sizeof(char));
    i = 0;
    j = 0;
    while (str1[i] != '\0' || str2[j] != '\0'){
        while (str1[i] == ' ' && str1[i] != '\0'){
            i++;
        }
        if (str1[i] != '\0'){
            result[k] = str1[i];
            k++;
            i++;
        }
        while (str2[j] == ' ' && str2[j] != '\0'){
            j++;
        }
        if (str2[j] != '\0'){
            result[k] = str2[j];
            k++;
            j++;
        }
    }
    result[k] = '\0';    
    return result;
}



int main(){
    char *str1 = "<  >";
    char *str2 = ">>";
    char *result = pile(str1,str2);
    printf("%s",result);
    return 0;
}