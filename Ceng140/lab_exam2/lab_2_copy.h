#ifndef _LAB_2_
#define _LAB_2_

/*
    This function finds the power of two using the given input.
    For example, if given number is 64 then this function will return 6 (2^6 = 64)

    n: input value
*/
int what_is_power(int n);

/*
    This function starts a game between 3 player. What this players do is given. 
    This function gives the initial number to the first player and 
    prints the winner and how many steps this game last till the end.

    n: starting number
*/
void find_13_winner(int n);

/*
    This function takes a string containing digits. It calculates the sum of 
    these digits and continue to do that until there left just one digit. It prints 
    all of the strings during each step and whether the last string even or odd.

    number: input string containing digits.
    len: length of the string
*/
void is_even_or_odd(char *number, int len);

/*
    This function finds and prints all subsets of the given array so that 
    the number of negative elements in each subset is more than the number of
    positive elements.

    numbers: given array containing numbers
    len: length of the given array
*/
void more_negative_subsets(int *numbers, int len);

#endif