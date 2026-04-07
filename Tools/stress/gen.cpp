#include <bits/stdc++.h>
#include "genlib.hpp"
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n = 5000;
    constexpr int L = -1e7, R = 1e7;
    auto x = gen::seq::array(n, L, R), y = gen::seq::array(n, L, R);
    cout << n << endl;
    for(int i = 0;i < n;i++){
        cout << x[i] << " " << y[i] << endl;
    }
    return 0;
}