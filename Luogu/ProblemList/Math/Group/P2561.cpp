#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

template<class T>
constexpr T power(T a, i64 b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}

void solve()
{
    int n;
    cin>>n;
    int ans = 0;
    int N = n * (n + 1) / 2;
    vector<int>f(21),g(21);
    f[0] = g[0] = 0;
    f[1] = g[1] = 1;
    for(int i = 2;i <= 20;i++){
        if(i % 2 == 0){
            f[i] = f[i / 2 - 1] + g[i / 2];
            g[i] = g[i - 1] + i / 2;
        }
        else{
            f[i] = f[i / 2 + 1] + g[i / 2];
            g[i] = g[i - 1] + i / 2 + 1;
        }
    }
    ans += power(2, N);
    ans += 2 * power(2, (N + 2) / 3);
    ans += 6 * power(2, g[n]);
    ans += 3 * power(2, g[n]);
    ans /= 12;
    cout<<ans<<endl;
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}