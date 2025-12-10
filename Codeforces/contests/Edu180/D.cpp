#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n;
    cin>>n;
    vector<vector<int>>g(n);
    vector<int>deg(n);
    for(int i = 0;i < n - 1;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        g[u].push_back(v);
        g[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }
    
    int ok = 0;
    int mid = -1;
    for(int i = 0;i < n;i++){
        if(deg[i] == 2){
            ok = 1;
            mid = i;
        }
    }
    if(!ok){
        cout<<"No"<<endl;
        return;
    }
    cout<<"Yes"<<endl;
    vector<int>clr(n);
    vector<int>fa(n, -1);
    fa[g[mid][0]] = fa[g[mid][1]] = mid;
    clr[g[mid][0]] = 1;
    //fa[leaf] = -1;
    auto dfs = [&](auto&&self, int p)->void
    {
        for(auto s : g[p]){
            if(s != fa[p]){
                fa[s] = p;
                clr[s] = clr[p] ^ 1;
                self(self, s);
            }
        }
    };
    dfs(dfs,g[mid][0]);
    dfs(dfs,g[mid][1]);
    
    for(int i = 0;i < n;i++){
        if(i != mid){
            if(clr[i] == 0){
                cout<<fa[i] + 1<<" "<<i + 1<<endl;
            }else{
                cout<<i + 1<<" "<<fa[i] + 1<<endl;
            }
        }
    }
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}