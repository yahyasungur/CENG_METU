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
vector<int> indexes;
#define d 1000005
#define REHASH(a, b, h) ((((h) - (a)*d) << 1) + (b))
const int P_B= 227;
const int P_M = 1000005;
const int T_S = 1000005;
class HashTableEntry {
public:
    int k;
    int v;
    HashTableEntry(int k, int v) {
        this->k= k;
        this->v = v;
    }
};
class HashMapTable {
private:
    HashTableEntry **t;
public:
    HashMapTable() {
        t = new HashTableEntry * [T_S];
        for (int i = 0; i< T_S; i++) {
            t[i] = NULL;
        }
    }
    int HashFunc(int k) {
        return k % T_S;
    }
    void Insert(int k, int v) {
        int h = HashFunc(k);
        while (t[h] != NULL && t[h]->k != k) {
            h = HashFunc(h + 1);
        }
        if (t[h] != NULL)
            delete t[h];
        t[h] = new HashTableEntry(k, v);
    }
    bool SearchKey(int k) {
        int h = HashFunc(k);
        while (t[h] != NULL && t[h]->k != k) {
            h = HashFunc(h + 1);
        }
        if (t[h] == NULL)
            return false;
        else
            return true;
    }
    ~HashMapTable() {
        for (int i = 0; i < T_S; i++) {
            if (t[i] != NULL)
            delete t[i];
            delete[] t;
        }
    }
};




int hashh(const string& s, int size){
    int r = 0;
    for (int i = 0; i < size; i++) {
        r = r* P_B + s[i];
        r %= P_M;
    }
    return r;
}

void rabinKarp(string strBig, vector<string> strSubs, long q, int K, int M, int N){
    HashMapTable hash;
    for (int i = 0; i < K; i++){
        hash.Insert(hashh(strSubs[i],M),1);
    }
    
    int hy = hashh(strBig.substr(0,M),M);

    for (int j = 0; j < N-M; j++){
        for (int k = 0; k < K; k++){
            if (hash.SearchKey(hy) && strBig.substr(j,M) == strSubs[k]){
                indexes.push_back(j);
            }
            hy = REHASH(strBig[j],strBig[j+M],hy);
        }
    }
}


vector<int> the8(const string& text, const vector<string>& patterns){

    vector<int> shifts; //DO NOT CHANGE THIS

    int N = (int)text.size();
    int M = (int)patterns[0].size();
    int q = 7919; //prime number
    int K = (int)patterns.size();

    rabinKarp(text,patterns,q,K,M,N);
    
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