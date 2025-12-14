#include<bits/stdc++.h>

#define int long long
using ll = long long;
using namespace std;

constexpr int P = 998244353;

int power(int a, int p)
{
    int res = 1;
    while(p){
        if(p & 1) res = 1ll * res * a % P;
        a = 1ll * a * a % P;
        p >>= 1;
    }
    return res;
}

int inv(int x)
{
    return power(x, P - 2);
}

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>>g(n);
    for(int i = 0;i < n - 1;i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<vector<int>>dp0(n),dp1(n);

    auto dfs = [&](auto&&self, int p, int fa)->void
    {
        dp0[p] = {1};
        dp1[p] = {0, 1};
        for(auto s : g[p]){
            if(s != fa){
                self(self, s, p);
                //dp0 = dp0p * dp1s
                {
                    int x = dp0[p].size(), y = dp1[s].size();
                    vector<int>ndp(x + y - 1);
                    for(int i = 0;i < x;i++){
                        for(int j = 0;j < y;j++){
                            ndp[i + j] = (ndp[i + j] + 1ll * dp0[p][i] * dp1[s][j]) % P;
                        }
                    }
                    dp0[p] = move(ndp);
                }
                //
                {
                    int x = dp1[p].size(), y = max(dp0[s].size(), dp1[s].size());
                    vector<int>dps(y);
                    for(int i = 0;i < dp0[s].size();i++){
                        dps[i] += dp0[s][i];
                        dps[i] %= P;
                    }
                    for(int i = 0;i < dp1[s].size();i++){
                        dps[i] += dp1[s][i];
                        dps[i] %= P;
                    }
                    vector<int>ndp(x + y - 1);
                    for(int i = 0;i < x;i++){
                        for(int j = 0;j < y;j++){
                            ndp[i + j] = (ndp[i + j] + 1ll * dp1[p][i] * dps[j]) % P;
                        }
                    }
                    dp1[p] = move(ndp);
                }
            }
        }
    };

    dfs(dfs, 0, -1);

    vector<int>f(n + 1);
    vector<int>fac(n + 1);
    vector<int>invfac(n + 1);
    invfac[0] = fac[0] = 1;
    for(int i = 1;i <= n;i++){
        fac[i] = 1ll * fac[i - 1] * i % P;
        invfac[i] = inv(fac[i]);
    }

    for(int i = 0;i < dp0[0].size();i++){
        f[i] += dp0[0][i];
    }

    for(int i = 0;i < dp1[0].size();i++){
        f[i] += dp1[0][i];
    }
    
    for(int i = 0;i <= n;i++){
        f[i] = 1ll * f[i] * fac[i] % P;
    }


    vector<int>G(n + 1);
    G[0] = f[0];

    for(int i = 1;i <= n;i++){
        G[i] = ((f[i] - 1ll * f[i - 1] * (n - i + 1)) % P + P) % P;
    }
    
    vector<int>cnt(n + 1);
    cnt[0] = 0;
    for(int i = 1;i <= n;i++){
        cnt[i] = (cnt[i - 1] + 1ll * n * inv(n - i + 1)) % P;
    }
    ll ans = 0;
    for(int i = 0;i <= n;i++){
        ans = (ans + 1ll * G[i] * cnt[i] % P * invfac[n] % P * fac[n - i] % P) % P;
    }
    cout << ans << endl;
    return;
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}
