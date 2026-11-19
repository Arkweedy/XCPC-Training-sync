#include <bits/stdc++.h>

using ll = long long;
using i64 = long long;

using namespace std;


int main()
{
    mt19937 g(random_device{}());
    cout << 1 << endl;
    i64 n = g() % 5 + 1;

    cout << n << " " << g() % (n * (n + 1) / 2) + 1 << endl;
    for(int i = 0;i < n;i++){
        cout << g() % 10000000 + 1 << " ";
    }
    cout << endl;
    return 0;
}