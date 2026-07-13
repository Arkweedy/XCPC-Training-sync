#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.07.13 17:05:49

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<vector<int>>a(n + 1, vector<int>(n + 1));
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            cin >> a[i][j];
        }
    }

    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            a[i][j] += a[i - 1][j];
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            a[i][j] += a[i][j - 1];
        }
    }
 
    auto w = [&](int l, int r)->int
    {
        return (a[r][r] - a[r][l - 1] - a[l - 1][r] + a[l - 1][l - 1]) / 2;
    };

    constexpr int inf = 1e9;
    vector<int>f(n + 1, inf);
    f[0] = 0;
    for(int i = 0;i < k;i++){
        vector<int>g(n + 1, inf);
        auto cdq = [&](auto&&self, int l, int r, int optL, int optR)->void
        {
            // if(l > r)return;
            // if(l == r){
            //     for(int i = optL;i <= optR;i++){
            //         g[l] = min(g[l], f[i - 1] + w(i, l));
            //     }
            //     return;
            // }
            int m = l + r >> 1;
            int optM = 0;
            int upper = min(optR, m);
            for(int i = optL;i <= upper;i++){
                int v = f[i - 1] + w(i, m);
                if(v <= g[m]){
                    g[m] = v;
                    optM = i;
                }
            }
            if(l <= m - 1)self(self, l, m - 1, optL, optM);
            if(m + 1 <= r)self(self, m + 1, r, optM, optR);
            return;
        };
        int group = i + 1;
        cdq(cdq, group, n, group, n);
        f = move(g);
    }
    int ans = f[n];
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