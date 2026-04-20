#include <bits/stdc++.h>
#include "genlib.hpp"
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    constexpr int P = 998244353;
    cout << 50 << endl;
    for(int i = 0;i < 50;i++){
        cout << gen::rnd::rand_u32(1, P - 1) % P << endl;
    }
    return 0;
}