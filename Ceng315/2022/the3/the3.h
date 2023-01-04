#ifndef HEADER_FILE
#define HEADER_FILE

#include <iostream>
#include <climits>
#include <cmath>
#include <cstdlib>

int recursive_sln(int i, char**& arr, int*& len, int &number_of_calls);
int memoization_sln(int i, char**& arr, int*& len, int**& mem);
int dp_sln(int size, char**& arr, int*& len, int**& mem);

#endif