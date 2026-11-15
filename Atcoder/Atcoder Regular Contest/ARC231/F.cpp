#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.10.06 14:56:23

void solve()
{
    int n;
    cin >> n;
    int N = 1 << n;
    int M = 1 << n - 1;
    vector<int>a(N);
    auto dfs = [&](this auto&&dfs, int p, int rk, int dep)->void
    {
        if(dep == n){
            a[p] = M + rk;
            return;
        }
        int b = 1 << n - dep - 1;
        int d = 1 << n - dep;
        a[p] = b + d * rk;
        int k = 1 << dep - 1;
        dfs(p * 2, k - rk - 1, dep + 1);
        dfs(p * 2 + 1, k + rk, dep + 1);
        return;
    };
    dfs(1, 0, 1);
    for(int i = 1;i < N;i++){
        cout << a[i] << " ";
    }
    cout << endl;
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