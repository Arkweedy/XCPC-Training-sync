#include <bits/stdc++.h>
#include "genlib.hpp"
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    cout << T << endl;
    int n = 2;
    int a = gen::rnd::uniform(1,100000);
    cout << a << " " << n << endl;
    gen::io::print_vec(cout, gen::seq::array_distinct(n, 0, 9));
    return 0;
}