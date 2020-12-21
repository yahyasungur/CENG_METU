#include <stdio.h>
#include "recit_4_1.h"


int gcd(int a, int b){
    
    int k,temp,n = b;
    
    printf("gcd %d %d\n",a,b);
    
    if(b > a){
        temp = a;
        a = b;
        b = temp; 
    }

    if (a%b != 0){
        k = a/b;
        n = gcd(b,a-b*k);
    }
    return n;
}

double helper(int base,int exponent,int call){
    
    double stored;

    printf("calculate: %d^%d call: %d\n",base,exponent,call);
    
    if(exponent == 0){
        return 1.0;
    }
    else if(exponent == 1){
        return (double)base;
    }
    else if (exponent%2 == 0){
        stored = helper(base,exponent/2,++call);    
        return stored*stored;
    }
    
    return base*helper(base,exponent-1,++call);    
}

double power(int base, int exponent){
    double result;
    result = helper(base,exponent,1);
    return result;
}
