#include <iostream>
#include <vector>

using namespace std;

vector<vector<long long>> memo(1001, vector<long long>(1001, -1)); // memoization table

// combination function using memoization
long long combination(int n, int r) {
    if (r == 0 || r == n) {
        return 1;
    }
    if (memo[n][r] != -1) {
        return memo[n][r];
    }
    memo[n][r] = combination(n - 1, r - 1) + combination(n - 1, r);
    return memo[n][r];
}

int main() {
    int n, r;
    cout << "Enter n and r: ";
    cin >> n >> r;
    if (r > n) {
        cout << "Invalid input!" << endl;
        return 0;
    }
    long long result = combination(n, r);
    cout << "The result of " << n << "C" << r << " is " << result << endl;
    return 0;
}