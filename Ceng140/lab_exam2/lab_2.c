#include <stdio.h>
#include "lab_2_copy.h"
#include "helper.h"

/* TASK SOLUTIONS */

/*
This function finds the power of two using the given input.
For example, if given number is 64 then this function will return 6 (2^6 = 64)
*/
int what_is_power_helper(int n, int k){
    
    if (n / 2 == 1){
        return k+1;
    }
    else if (n == 0){
        return 0;
    }
    else{
        return what_is_power_helper(n/2,k+1);
    }
}

int what_is_power(int n){
    return what_is_power_helper(n,0);
}

/*
    This function starts a game between 3 player. What this players do is given. 
    This function gives the initial number to the first player and 
    prints the winner and how many steps this game last till the end.

    n: starting number
*/

void print_13(char player, int n, int step){
    printf("Player %c n: %d\n",player,n);
    if (n % 13 == 0){
        printf("Winner: %c, steps: %d\n",player,step);
    }
}

void find_13_winner_B(int n, int step);
void find_13_winner_C(int n, int step);

void find_13_winner_A(int n, int step){
    n += 13;
    print_13('A',n,step+1);
    if (n % 13 == 0){
        return;
    }
    if(n % 2 == 0){
        find_13_winner_B(n,step+1);
    }
    else{
        find_13_winner_C(n,step+1);
    }
}
void find_13_winner_B(int n, int step){
    n /= 2;
    print_13('B',n,step+1);
    if (n % 13 == 0){
        return;
    }
    if(n % 2 == 0){
        find_13_winner_A(n,step+1);
    }
    else{
        find_13_winner_C(n,step+1);
    }
}
void find_13_winner_C(int n, int step){
    n = (n-3)/2;
    print_13('C',n,step+1);
    if (n % 13 == 0){
        return;
    }
    
    if(n % 2 == 0){
        find_13_winner_A(n,step+1);
    }
    else{
        find_13_winner_B(n+1,step+1);
    }
}

void find_13_winner(int n){
    find_13_winner_A(n,0);
}

/*
    This function takes a string containing digits. It calculates the sum of 
    these digits and continue to do that until left just one digit. It prints 
    all of the strings during each step and whether the last string even or odd.

    number: input string containing digits.
    len: length of the string
*/
int is_even_or_odd_helper(char *number, int len, int sum){
    if (len == 1){
        printf("%c\n",number[0]);
        sum += ((int)number[0]-48);
        return sum;
    }
    else{
        printf("%c",number[0]);
        sum += ((int)number[0]-48);
        return is_even_or_odd_helper(&number[1],len-1,sum);
    }
}


void is_even_or_odd(char *number, int len){
    int sum;
    int length;

    sum = is_even_or_odd_helper(number,len,0);
    number = convert_to_char_array(sum, &length);
    if (length != 1){
        is_even_or_odd(number,length);
    }
    else{
        printf("%s\n",number);
        if ((int)number[0] % 2 == 1){
            printf("It is odd.\n");
        }
        else{
            printf("It is even.\n");
        }
    }
}

/*
    This function finds and prints all subsets of the given array so that 
    the number of negative elements in each subset is more than the number of
    positive elements.

    numbers: given array containing numbers
    len: length of the given array
*/




void is_it_zero(int *arr,int length){
	int i,neg = 0,pos =0;
	
	for ( i = 0; i < length; i++){
		if (arr[i] < 0){
			neg++;
		}
        else if(arr[i] > 0){
            pos++;
        }	
	}


	if (neg > pos){
		printf("{");
		for ( i = 0; i < length; i++){
			if (arr[i] != 0){
			printf("%d ",arr[i]);
			}
		}
		printf("}\n");
	}

}

void sum_zero_subsets_helper(int *array,int len, int index){
	int i;
	int arr[50];

	for ( i = 0; i < len; i++){
		arr[i] = array[i];
	}

	if (index == len){
		is_it_zero(arr,len);
		return;
	}
	sum_zero_subsets_helper(arr,len,index+1);
	*(arr+index) = 0;
	sum_zero_subsets_helper(arr,len,index+1);

}


void more_negative_subsets(int *numbers, int len){
    sum_zero_subsets_helper(numbers,len,0);
    /* Write your code here */
}