//This file is entirely for your test purposes.
//This will not be evaluated, you can change it and experiment with it as you want.
#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
//#include "the2.h"

//--------------------------------------------

//#include "the2.h"
#include <cmath>
// You may write your own helper functions here
bool flag = false;

int countSort(int *arr, int n, int exp, int groupSize,int size) {
	int numberOfIterations = 0;

    int output[n]; // output array
    int divident = ((int)(pow(10, groupSize)));
	int i, count[size] = {0};

    // Store count of occurrences in count[]
    for (i = 0; i < n; i++){
        numberOfIterations++;
        count[ (arr[i]/exp) % divident]++;
    }

    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < size; i++){
        numberOfIterations++;
        count[i] += count[i - 1];
    }

    for (i = n - 1; i >= 0; i--){
        numberOfIterations++;
        output[count[ (arr[i]/exp) % divident]-1] = arr[i];
        count[ (arr[i]/exp) % divident]--;
    }

    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++){
		numberOfIterations++;
		arr[i] = output[i];
	}

	return numberOfIterations;
}

long multiDigitRadixSort(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength){
    long numberOfIterations = 0;
    
	if (maxDigitLength < groupSize){
		groupSize = maxDigitLength;
	}
	int size;
	int exp = 1;
    for (int i = maxDigitLength; i > 0 ; i-=groupSize){
		if (i < groupSize){
			groupSize = i;
		}
		size = (int)(pow(10, groupSize));
        numberOfIterations += countSort(arr, arraySize, exp, groupSize, size);
		exp*=(int)(pow(10, groupSize));
    }

	if(ascending == false){
		int temp;
		for(int i = 0; i < arraySize/2; i++){
			temp = arr[i];
			arr[i] = arr[arraySize-i-1];
			arr[arraySize-i-1] = temp;
		}
	}

    return numberOfIterations;
}

//--------------------------------------------



// the2.h only contains declaration of the function:
// int multiDigitRadixSort(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength)

using namespace std;

void randomFill(int*& arr, int size, int minval, int interval){
	arr = new int [size];
	for (int i = 0; i < size; i++)
	{
		arr[i] = minval + (random() % interval);
	}
}

void print_to_file(int* arr, int size, long numberOfIterations){
	ofstream ofile;
	ofile.open("outsol04.txt");
    ofile << numberOfIterations << endl;
    ofile << size << endl;
	for(int i = 0; i < size; i++)
		ofile << arr[i] << endl;
}

void read_from_file(int*& arr, int& size, bool& ascending, int& groupSize, int& maxDigitLength){

	char addr[]= "input04.txt";
	ifstream infile (addr);
	if (!infile.is_open())
	{
		cout << "File \'"<< addr
			<< "\' can not be opened. Make sure that this file exists." <<endl;
		return;
	}
  infile >> ascending;
  infile >> groupSize;
  infile >> maxDigitLength;
  infile >> size;
	arr = new int [size];

	for (int i=0; i<size;i++) {

		infile >> arr[i];
	}
}


void test(int* arr, bool ascending, int groupSize, int maxDigitLength, int array_size){

	clock_t begin, end;
	double duration;
    long iterations=0;
	// Print initial array
    cout << "Array size: " << array_size << endl
         << "Group size: : " << groupSize << endl
         << "Max Digit Length: " << maxDigitLength << endl 
         << "Ascending: ";
    if(ascending){
        cout << "True" << endl << endl;
    }else{
        cout << "False" << endl << endl;
    }
    cout << "Initial Array: {";
    for(int i=0; i<array_size; i++){
        cout << arr[i];
        if(i != array_size-1) cout << ", ";
    }
    cout << "}" << endl;
    
    // Function call and and calculate the duration
    if ((begin = clock() ) ==-1)
		cerr << "clock error" << endl;
		
    iterations = multiDigitRadixSort(arr, ascending, array_size, groupSize, maxDigitLength);
    
    if ((end = clock() ) ==-1)
		cerr << "clock error" << endl;

    
	cout << "Sorted Array: {";
    for(int i=0; i<array_size; i++){
        cout << arr[i];
        if(i != array_size-1) cout << ", ";
    }
    cout << "}" << endl << endl;
    
	duration = ((double) end - begin) / CLOCKS_PER_SEC;
	cout << "Duration: " << duration << " seconds." <<endl;
	cout << "Number of iterations: " << iterations << endl;
	print_to_file(arr, array_size, iterations);
	// Calculation and output end
}

int main(){
    int size = 5;
	int groupSize = 1;
	int maxDigitLength = 3;
	int minval = 0;
	int interval = 900;
	int *arr;
	bool ascending = true;
    // Randomly generate initial array:
	srandom(time(0));
	randomFill(arr, size, minval, interval);
	// int array[5] = {4,1,3,4,3};
    // Read the test inputs. input01.txt through input04.txt exists.
    read_from_file(arr, size, ascending, groupSize, maxDigitLength);
	test(arr, ascending, groupSize, maxDigitLength, size);
	cout << endl;
	return 0;
}
