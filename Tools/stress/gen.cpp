#include <bits/stdc++.h>
#include "genlib.hpp"
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n = 5;
    auto a = gen::seq::array<int>(n, 1, 10);
    cout << n << endl;
    gen::io::print_vec(cout, a);
    return 0;
}