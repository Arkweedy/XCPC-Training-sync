#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e5 + 10;

struct tree{

    int n;
    vector<vector<int>>e;
    int dist;
    void init( vector<pair<int,int>> & edges){
        n = edges.size() + 1;
        e.assign(n + 1,{});
        dist = 0;
        for(auto [u,v]:edges){
            e[u].push_back(v);
            e[v].push_back(u);
        }
        dfs(1,0);
    }
    
    int dfs(int u,int f){
        int mx = 0;
        for(auto v:e[u]){
            if(v==f)continue;
            int t = dfs(v,u) + 1;
            dist = max(dist,t + mx);
            mx = max(t,mx);
        }
        return mx;
    }
};

void solve()
{
    int n,k;cin>>n>>k;
    vector<int>d(2*k),p(2*k);
    for(int i=0;i<2*k;i++){
        vector<pair<int,int>>e;
        for(int j=0;j<n-1;j++){
            int u,v;cin>>u>>v;
            e.push_back({u,v});
        }
        tree tr;
        tr.init(e);
        d[i] = tr.dist;
        p[i] = i;
    }
    sort(p.begin(),p.end(),[&](int i,int j){
        return d[i] < d[j];
    });
    
    vector<int>ans(2*k);
    for(int i=0;i<k;i++)ans[p[i]] = 0;
    for(int i=k;i<2*k;i++)ans[p[i]] = 1;
    for(int i=0;i<2*k;i++){
        if(ans[i])cout<<"Uniform\n";
        else cout<<"DSU\n";
    }
}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int t = 1;
    while(t--){
        solve();
    }
    return 0;
}
