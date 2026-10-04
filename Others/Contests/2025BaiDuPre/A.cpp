#include<bits/stdc++.h>

using ll = long long;
using namespace std;

void solve()
{
    int n;
    cin>>n;
    vector<vector<int>>g(n);
    for(int i = 0;i < n-1;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    // clr[0] = 0;
    // dfs(dfs, 0, -1);
    //int odd = count(clr.begin(),clr.end(), 0), even = count(clr.begin(),clr.end(), 1);
    //ll ans = 1ll * odd * (odd - 1) / 2 + 1ll *  even * (even - 1) / 2;
    ll ans = 1ll * n * (n - 1);
    for(int i = 0;i < n;i++){
        ans -= g[i].size();
    }
    ans /= 2;
    //delete leaf pair that dis = 3
    vector<array<int,3>>cnt(n,array<int,3>{});//dis = 1, 2
    auto dfs = [&](auto&&self, int p, int fa)->void
    {
        for(auto s : g[p]){
            if(s != fa){
                self(self, s, p);
                cnt[p][1] += cnt[s][0];
                cnt[p][2] += cnt[s][1];
            }
        }
        if(g[p].size() == 1){
            cnt[p] = {1,0,0};
        }
        else{
            ans -= 1ll * cnt[p][1] * cnt[p][2];
        }
    };
    for(int i = 0;i < n;i++){
        if(g[i].size() > 1){
            dfs(dfs,i, -1);
            break;
        }
    }

    cout<<ans<<endl;
    return;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt = 1;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}
