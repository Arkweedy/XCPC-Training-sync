#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.07.16 16:29:50
int lowbit(int x)
{
    return x & -x;
}

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>>a(n, vector<int>(n));
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            cin >> a[i][j];
        }
    }

    int m = 1 << n;
    vector<i64>w(m), f(m);
    for(int i = 1;i < m;i++){
        int p = __lg(lowbit(i));
        w[i] = w[i ^ (1 << p)];
        for(int j = 0;j < n;j++){
            if((i >> j) & 1)w[i] += a[p][j];
        }
    }

    for(int i = 1;i < m;i++){
        for(int s = i;s > 0;s = (s - 1) & i){
            f[i] = max(f[i], f[i ^ s] + w[s]);
        }
    }

    i64 ans = f[m - 1];
    cout << ans << endl;
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