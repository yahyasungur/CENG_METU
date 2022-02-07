//#include "the8.h"
#include<iostream>
#include<climits>
#include<cmath>
#include<string>
#include<ctime>
#include<string>
#include<vector>
#include<array>
#include<list>
#include<forward_list>
#include<cmath>
#include<random>
#include<cstring>
#include<cstdlib>

//DO NOT ADD OTHER LIBRARIES

using namespace std;

// d is the number of characters in the input alphabet
#define d 26
vector<int> indexes;

/* pat -> pattern
    txt -> text
    q -> A prime number
*/
void search(string pat, string txt, long q, int M, int N){
    int i, j;
    long p = 0; // hash value for pattern
    long t = 0; // hash value for txt
    long h = 1;

    // The value of h would be "pow(d, M-1)%q"
    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;

    // Calculate the hash value of pattern and first
    // window of text
    for (i = 0; i < M; i++)
    {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= N - M; i++)
    {

        // Check the hash values of current window of text
        // and pattern. If the hash values match then only
        // check for characters one by one
        if ( p == t ){
            /* Check for characters one by one */
            for (j = 0; j < M; j++){
                if (txt[i+j] != pat[j]){
                    break;
                }
            }

            // if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1]
        
            if (j == M)
                //cout<<"Pattern found at index "<< i<<endl;
                indexes.push_back(i);
        }

        // Calculate hash value for next window of text: Remove
        // leading digit, add trailing digit
        if ( i < N-M ){
            t = (d*(t - txt[i]*h) + txt[i+M])%q;

            // We might get negative value of t, converting it
            // to positive
            if (t < 0)
            t = (t + q);
        }
    }
}

vector<int> the8(const string& text, const vector<string>& patterns){

    vector<int> shifts; //DO NOT CHANGE THIS

    int N = (int)text.size();
    int M = (int)patterns[0].size();
    long q = 1000005; //prime number
    int K = (int)patterns.size();

    for (int i = 0; i < K; i++){
        search(patterns[i], text, q, M, N);
    }

    indexes.shrink_to_fit();
    shifts = indexes;

    return shifts; //DO NOT CHANGE THIS
}


int main(){
    string text = "abcdefgijbcde";
    vector<string> patterns = {"bcde", "defg", "qwer", "uutz"};

    vector<int> shifts = the8(text, patterns);
    int size = (int)shifts.size();

    cout << "{";
    for (int i = 0; i < size; i++){
        if (i == size-1){
            cout << shifts[i];
            continue;
        }
        
        cout << shifts[i] << ", ";
    }
    cout << "}" << endl;

    return 0;
}
