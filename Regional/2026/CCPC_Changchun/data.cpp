#include<bits/stdc++.h>

using ll = long long;
using i64 = long long;

using namespace std;

int main()
{
    cout << 1 << endl;
    mt19937 g(chrono::steady_clock::now().time_since_epoch().count());
    int n = g() % 8 + 1;
    string s;
    for(int i = 0;i < n;i++){
        if(g () % 2)s += '1';
        else s += '0';
    }
    cout << s << endl;
    return 0;
}