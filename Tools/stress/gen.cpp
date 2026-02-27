#include <bits/stdc++.h>
#include "genlib.hpp"
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << 1<< endl;
    int s = gen::rnd::uniform(1,20), m = gen::rnd::uniform(1,20);
    cout << s << " " << m << endl;
    return 0;
}