#include <iostream>
#include <math.h>
#include <map>
#include <numeric>

#define MOD 8191

using namespace std;

// Create a map to store the number of connected case for dynamic programming
map<tuple<int,int,int>, int> connectedMap;
// Create a map to store the number of combination for dynamic programming
map<tuple<int,int>, int> combinationMap;
// Create a map to store the number of disconnected case for dynamic programming
map<tuple<int,int>, int> disconnectedMap;
// Create a map to store the number of connectedWithDifference case for dynamic programming
map<tuple<int,int>, int> connectedWithDifferenceMap;
// Create a map to store the number of all case for dynamic programming
map<tuple<int,int>, int> allMap;


int connectedWithDifference(int W, int H);


// Function to find the nCr
int NcR(int n, int r){
    int _n = n;
    int _r = r;
    // if combinationMap contains the case, use it
    if(combinationMap.find(make_tuple(n,r)) != combinationMap.end()){
        return combinationMap[make_tuple(n,r)];
    }

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
    combinationMap[make_tuple(_n,_r)] = p % MOD;
    return p % MOD;
}


int connected(int W, int H, int k, int l){
    // Base case
    if (W == 0){
        return 0;
    } if (W == 1){
        return 1;
    }
    
    int n = 0;
    if(connectedMap.find(make_tuple(W,k,l)) != connectedMap.end()){
    // If the case is already in the map use it
        n = connectedMap[make_tuple(W,k,l)];
    } else {
        // If the case is not in the map, calculate it
        if (W == 2){
            int i = 0;
            if (l == 0){
                i = 1;
            }
            for (; i <= H-k-l; i++){
                n += (NcR(H-k-l, i) * connected(W-1, H, i+l, 0));
                n = n % MOD;
            }
        } else{
            if (l > 0){
                for (int i = 0; i <= H-k-l; i++){
                    for (int j = 0; j <= H-k-l-i; j++){
                        n += (((NcR(H-k-l, i) * NcR(H-k-l-i,j)) % MOD) * connected(W-1, H, i+l, j));
                        n = n % MOD;
                    }
                }
            } else{
                for (int i = 0; i <= H-k-l; i++){
                    if (i == 0){
                        for (int j = 1; j <= H-k-l-i; j++){
                            n += (((NcR(H-k-l, i) * NcR(H-k-l-i,j)) % MOD) * connected(W-1, H, i+l, j));
                            n = n % MOD;
                        }
                    } else {
                        for (int j = 0; j <= H-k-l-i; j++){
                            n += (((NcR(H-k-l, i) * NcR(H-k-l-i,j)) % MOD) * connected(W-1, H, i+l, j));
                            n = n % MOD;
                        }
                    }
                }
            }
        }

        connectedMap[make_tuple(W,k,l)] = n;
    }

    return n;
}

int row(int W){
    if (W == 0){
        return 0;
    }else if (W == 1){
        return 1;
    } else if (W == 2){
        return 2;
    } else if(W == 3){
        return 4;
    }
    else{
        return row(W-1) + row(W-2) + row(W-3);
    }
}

int all(int W, int H){
    // If the case is already in the map use it
    if(allMap.find(make_tuple(W,H)) != allMap.end()){
        return allMap[make_tuple(W,H)];
    } else {
        // If the case is not in the map, calculate it
        allMap[make_tuple(W,H)] = pow(row(W), H);
    }

    return allMap[make_tuple(W,H)];
}

int disconnected(int W, int H){
    int n = 0;

    // If the case is already in the map use it
    if(disconnectedMap.find(make_tuple(W,H)) != disconnectedMap.end()){
        n = disconnectedMap[make_tuple(W,H)];
    } else {
        // If the case is not in the map, calculate it
        for(int i = 1 ; i <= W-1; i++){
            n += connectedWithDifference(i, H) * all(W-i, H);
            n = n % MOD;
        }
        disconnectedMap[make_tuple(W,H)] = n;
    }

    return n;
}

int connectedWithDifference(int W, int H){
    // if the case is already in the map, use it
    if(connectedWithDifferenceMap.find(make_tuple(W,H)) != connectedWithDifferenceMap.end()){
        return connectedWithDifferenceMap[make_tuple(W,H)];
    } else{
        connectedWithDifferenceMap[make_tuple(W,H)] = (all(W,H) - disconnected(W,H))%MOD;
    }

    return connectedWithDifferenceMap[make_tuple(W,H)];
}


int main(){
    int W = 100, H = 100;
    //cin >> W >> H;
    long n;

    if (W*H*H*H*H > W*W){
        //n = connectedWithDifference(W, H);
        n = connectedWithDifference(W,H);
    } else {
        n = connected(W,H,0,0);
    }

    if (n < 0){
        n = n + MOD;
    }

    cout << n << endl;
    return 0;
}