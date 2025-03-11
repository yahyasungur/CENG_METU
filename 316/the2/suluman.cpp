#include <iostream>
#include <math.h>
#include <map>
#include <numeric>

#define MOD 8191

using namespace std;


int NcR(int n, int r){
    int suleyman = n;
    int muhtesem = r;
    // if combinationMap contains the case, use it
    // if(combinationMap.find(make_tuple(n,r)) != combinationMap.end()){
    //     return combinationMap[make_tuple(n,r)];
    // }

    long long p = 1, k = 1;

    if (n - r < r)
        r = n - r;

    if (r != 0) {
        while (r) {
            p *= n % MOD;
            k *= r % MOD;

            long long m = gcd(p, k) % MOD;

            p /= m;
            k /= m;

            n--;
            r--;
        }
    }
    else{
        p = 1;
    }

    // if our approach is correct p = ans and k =1
    //combinationMap[make_tuple(suleyman,muhtesem)] = p;
    return p;
}

int main(){
    cout << NcR(32,16) << endl;
}