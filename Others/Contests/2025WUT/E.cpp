#include<bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using uint = unsigned int;

using namespace std;

constexpr int P = 998244353;

ll qpow(ll a, int p)
{
    int res = 1;
    while(p != 0){
        if(p & 1){
            res = 1ll * res * a % P;
        }
        a = 1ll * a * a % P;
        p >>= 1;
    }
    return res;
}

ll inv(ll a)
{
    return qpow(a % P,P-2);
}

ll dec(ll a, ll b)
{
    return (a - b + P) % P;
}

void solve()
{
    int n;
    cin>>n;
    vector<int>a(n),b(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    for(int i = 0;i < n;i++){
        cin>>b[i];
    }
    vector<ll>pos(n);
    for(int i = 0;i < n;i++){
        pos[i] = 1ll * a[i] * inv(b[i]) % P;
    }

    vector<vector<array<ll,5>>>dp(n,vector<array<ll,5>>(n + 1));//dp0, dp1, dpall, dpfa-p,dpfa^-1
    vector<vector<int>>g(n);
    vector<int>fa(n, -1);
    for(int i = 0;i < n - 1;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int root = 0;
    
    auto dfs = [&](auto&&self, int p)->void
    {
        for(int i = 0;i <= n;i++){
            dp[p][i][0] = dec(1,pos[p]);
            dp[p][i][1] = pos[p];
        }
        for(auto s : g[p]){
            if(fa[p] != s){
                fa[s] = p;
                self(self,s);
                for(int i = 0;i < n;i++){
                    dp[p][i][0] = dp[p][i][0] * (dp[s][i][0] + dp[s][i][1]) % P;
                }
                for(int i = 1;i <= n;i++){
                    dp[p][i][1] = dp[p][i][1] * (dp[s][i-1][0] + dp[s][i-1][1]) % P;
                }
            }
        }
        for(int i = 0;i <= n;i++){
            dp[p][i][2] = (dp[p][i][0] + dp[p][i][1]) % P;
        }
    };

    auto calc_dec = [&](int p)->void
    {
        int f = fa[p];
        //vector<ll>dpr(n + 1);
        for(int i = 0;i <= n;i++){
            dp[p][i][3] = dp[f][i][0] * inv(dp[p][i][2]) % P;
            if(i > 0)dp[p][i][3] +=  dp[f][i][1] * inv(dp[p][i - 1][2]) % P;
        }
    };

    dfs(dfs,root);
    for(int i = 1;i < n;i++){
        calc_dec(i);
    }

    auto rdfs = [&](auto&&self, int p)->void
    {
        if(p != root){
            
            for(int i = 0;i <= n;i++){
                dp[p][i][4] = dp[p][i][3];
            }
            if(fa[p] != root){
                //link fa-1 to p
                int f = fa[p];
                vector<ll>fp(n+ 1);
                for(int i = 0; i<=n;i++){
                    fp[i] = (dec(1, pos[p]) * dp[f][i][4] % P + (i > 0 ? 0 :  pos[f] * dp[f][i - 1][4] % P) ) % P;
                }
                for(int i = 0;i <= n;i++){
                    dp[p][i][4] = dec(1, dec(1, fp[i])*dec(1, dp[p][i][4]));
                }
            }
        }
        for(auto s : g[p]){
            if(s != fa[p]){
                self(self, s);
            }
        }
    };

    vector<vector<ll>>ans(n,vector<ll>(n + 1));
    for(int p = 1;p < n;p++){
        int f =fa[p];
        //link dpall <- dpr^-1
        vector<ll>fp(n+ 1);
        for(int i = 0; i<=n;i++){
            fp[i] = (dec(1, pos[p]) * dp[f][i][4] % P + (i > 0 ? 0 :  pos[p] * dp[f][i - 1][4] % P) ) % P;
        }
        for(int i = 0;i <= n;i++){
            ans[p][i] = dec(1, dec(1, fp[i])*dec(1, dp[p][i][2]));
        }
    }
    vector<ll>res(n + 1);
    for(int i = 0;i < n;i++){
        for(int j = 1;j <= n;j++){
            res[i] += j *(ans[i][j] - ans[i][j-1]) % P;
        }
        res[i] %= P;
        cout<<res[i]<<" ";
    }
    cout<<endl;


}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int tt = 1;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}