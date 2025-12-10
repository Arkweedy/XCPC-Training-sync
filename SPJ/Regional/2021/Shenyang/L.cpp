#include<bits/stdc++.h>

using ll = long long;

using namespace std;

constexpr int N = 1e5 + 10;
constexpr int P = 998244353;

vector<int> operator*(vector<int>lhs, vector<int>rhs)
{
    
    int x = lhs.size(), y = rhs.size();
    vector<int>res(x + y - 1);
    for(int i = 0;i < x;i++){
        for(int j = 0;j < y;j++){
            res[i + j] = (res[i + j] + 1ll * lhs[i] * rhs[j]) % P;
        }
    }
    return res;
}

vector<int> operator+(vector<int>lhs, vector<int>rhs)
{
    
    int x = max(lhs.size(),rhs.size());
    vector<int>res(x);
    for(int i = 0;i < x;i++){
        if(i<lhs.size()) res[i] = (res[i] + lhs[i]) % P;
        if(i<rhs.size()) res[i] = (res[i] + rhs[i]) % P;
    }
    return res;
}

vector<int> operator<<(vector<int>lhs, int k)
{
    
    vector<int>res(lhs.size() + 1);
    for(int i = 0;i < lhs.size();i++){
        res[i + 1] = lhs[i] % P;
    }
    return res;
}



void solve()
{
    int n;
    cin>>n;
    n *= 2;
    vector<vector<int>>g(n);
    for(int i = 0;i < n - 1;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    

    vector<vector<int>>dp0(n),dp1(n);
    
    auto dfs = [&](auto&&self, int p, int fa)->void
    {
        dp0[p] = {1};
        dp1[p] = {0};
        int cnt = 0;
        for(auto s : g[p]){
            if(s != fa){
                self(self, s, p);
                dp1[p] = dp1[p] * (dp0[s] + dp1[s]) + (dp0[p] * dp0[s] << 1);
                dp0[p] = dp0[p] * (dp0[s] + dp1[s]);
            }
        }
        return;
    };

    dfs(dfs,0,-1);

    // for(int i = 0;i < n;i++){
    //     cerr<<"node "<<i<<endl;
    //     for(auto x : dp0[i]){
    //         cerr<<x<<" ";
    //     }
    //     cerr<<endl;
    //     for(auto x : dp1[i]){
    //         cerr<<x<<" ";
    //     }
    //     cerr<<endl;
    // }
    // cerr<<endl;
    
    auto cnt = dp0[0] + dp1[0];
    cnt.resize(n / 2 + 1);
    vector<int>dfac(n + 1);
    dfac[0] = dfac[1] = 1;
    for(int i = 2;i <= n;i++){
        dfac[i] = 1ll * dfac[i - 2] * i % P;
    }

    
    int ans = 0;
    for(int i = 0;i <= n / 2;i++){
        //cerr<<cnt[i]<<" ";
        ans = ((ans + (i % 2 == 0 ? 1 : -1) * 1ll * dfac[max(n - i * 2 - 1, 0)] * cnt[i]) % P + P) % P;
    }
    //cerr<<endl;

    cout<<ans<<endl;
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin>>tt;
    while(tt--){
        solve();
    }
}