#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.10.29 14:49:47

void solve()
{
    int n;
    cin>>n;
    vector<ll>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    vector<vector<int>>g(n);
    for(int i = 1;i < n;i++){
        int u;
        cin>>u;
        u--;
        g[u].push_back(i);
    }

    vector<int>sz(n, 1);
    vector<ll>sum = a;

    auto dfs = [&](auto&&self, int p)->void
    {
        for(auto s : g[p]){
            self(self, s);
            sum[p] += sum[s];
            sz[p] += sz[s];
        }
        sort(g[p].begin(),g[p].end(), [&](int i, int j)->bool
        {
            return sz[i] * sum[j] > sz[j] * sum[i];
        });
        return;
    };

    ll ans = 0;
    int t = 1;
    auto get = [&](auto&&self, int p)->void
    {
        ans += t * a[p];
        t++;
        for(auto s : g[p]){
            self(self, s);
        }
        return;
    };

    dfs(dfs, 0);
    get(get, 0);

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