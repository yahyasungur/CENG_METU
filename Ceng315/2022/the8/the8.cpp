#include "the8.h"

using namespace std; 

void matchPattern(const std::string& sequence, const std::pair<std::string,std::string> mapping, const std::string& pattern){

    int size_of_pattern = pattern.size(); // store the size of pattern in size_of_pattern variable 
	int size_of_sequence = sequence.size(); // store the size of sequence in size_of_sequence variable 
	int mappings[size_of_pattern+1][95]; // declare the mappings array with size of pattern+1 and 95 
    int current, index,first_mapping, second_mapping,string_space=0; // declare the current, index, first_mapping, second_mapping and string_space variables

    // convert string to int array for sequence and pattern 
    for(int counter=0; counter<95; counter++){
        if(counter == mapping.first[0]){ // if the first mapping is found then store it in first_mapping variable
            first_mapping = mapping.first[0]; // store the first mapping in first_mapping variable
        }
        if(counter == mapping.second[0]){ // if the second mapping is found then store it in second_mapping variable
            second_mapping = mapping.second[0]; // store the second mapping in second_mapping variable
        }
    }

    for (current = 0; current <= size_of_pattern; ++current){ // loop for the size of pattern 
        for (index = 0; index < 95; ++index){ // loop for the size of sequence
            int flag=0; // flag variable to check if the mapping is found or not
            bool check1 = false; // check1 variable to check if the mapping is found or not
            if (index == pattern[current]) check1 = true; // if the index is equal to the pattern then check1 is true
            else if (index == first_mapping && pattern[current] == second_mapping) check1 = true; // if the index is equal to the first mapping and the pattern is equal to the second mapping then check1 is true
            else if (index == second_mapping && pattern[current] == first_mapping) check1 = true; // if the index is equal to the second mapping and the pattern is equal to the first mapping then check1 is true

            if (current < size_of_pattern && check1){ // if the current is less than the size of pattern and check1 is true then the mapping is found
                mappings[current][index] = current+1; // store the current+1 in the mappings array
                flag=1; // flag is set to 1
                continue; // continue the loop 
            }

            int iteration, i; // iteration and i variables are declared
            for (iteration = current; iteration > 0; iteration--) // loop for the current variable
            {
                bool check2 = false; // check2 variable is declared
                if (index == pattern[iteration-1]) check2 = true; // if the index is equal to the pattern then check2 is true
                else if (index == first_mapping && pattern[iteration-1] == second_mapping) check2 = true; // if the index is equal to the first mapping and the pattern is equal to the second mapping then check2 is true
                else if (index == second_mapping && pattern[iteration-1] == first_mapping) check2 = true; // if the index is equal to the second mapping and the pattern is equal to the first mapping then check2 is true
                if (check2) // if check2 is true then the mapping is found
                {
                    for (i = 0; i < iteration-1; i++){ // loop for the iteration-1 variable
                        bool check3 = false; // check3 variable is declared
                        if (pattern[i] == pattern[current-iteration+1+i]) check3 = true; // if the pattern is equal to the pattern then check3 is true
                        else if (pattern[i] == first_mapping && pattern[current-iteration+1+i] == second_mapping) check3 = true; // if the pattern is equal to the first mapping and the pattern is equal to the second mapping then check3 is true
                        else if (pattern[i] == second_mapping && pattern[current-iteration+1+i] == first_mapping) check3 = true; // if the pattern is equal to the second mapping and the pattern is equal to the first mapping then check3 is true
                        if (!check3){ // if check3 is false then the mapping is not found
                            break; // break the loop
                        }
                    }
                    if (i == iteration-1){ // if i is equal to the iteration-1 then the mapping is found
                        mappings[current][index] =  iteration; // store the iteration in the mappings array
                        flag=1; // flag is set to 1
                        break; // break the loop
                    }
                }
            }
            if(!flag) mappings[current][index] = 0; // if flag is 0 then store 0 in the mappings array 
        }
    }

    current=0; // set the current variable to 0 
	for (int counter2 = 0; counter2 < size_of_sequence; counter2++){ // loop for the size of sequence 
		current = mappings[current][(int)sequence[counter2]]; // store the mappings array in the current variable
		if (current == size_of_pattern){ // if the current is equal to the size of pattern then the pattern is found
            if(string_space){ // if string_space is true then print a space
                cout << " "; // print a space 
            } 
			cout<< counter2-size_of_pattern+1; // print the counter2-size_of_pattern+1
            string_space=1; // string_space is set to 1
        }
	}
    if(!string_space) cout << "NONE"; // if string_space is false then print NONE
}