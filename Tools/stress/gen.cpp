#include <bits/stdc++.h>
#include "genlib.hpp"
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const int N = 100;
    auto a = gen::seq::array(N, 0, 100000000);
    cout << N << endl;
    gen::io::print_vec(cout, a);
}