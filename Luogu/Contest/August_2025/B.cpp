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
    for(int i = 0;i < n- 1;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int>val(n);
    vector<int>dep(n);

    int len = __lg(n) + 1;
    vector<vector<int>>fa(n,vector<int>(len));
    
    auto dfs = [&](auto&&self, int p)->void
    {
        for(auto s : g[p]){
            if(s != fa[p][0]){
                dep[s] = dep[p] + 1;
                fa[s][0] = p;
                self(self, s);
                
            }
        }
    };
    dep[0] = 1;
    dfs(dfs, 0);

    for(int j = 1;j < len;j++){
        for(int i = 0;i < n;i++){
            fa[i][j] = fa[fa[i][j - 1]][j - 1];
        }
    }
    
    vector<int>res;
    vector<int>cnt(n);
    for(int i = 0;i < n;i++){
        int p = i;
        int up = dep[i] / 2;
        for(int j = 20;j >= 0;j--){
            if(up >> j & 1){
                p = fa[p][j];
            }
        }
        cnt[p]++;
    }

    auto dfs2 = [&](auto&&self ,int p)->vector<int>
    {
        vector<vector<int>>arr;
        vector<int>res;
        res.push_back(cnt[p]);
        for(auto s : g[p]){
            if(s != fa[p][0])
                arr.push_back(self(self, s));
        }
        
        
    };
    // priority_queue<pair<int,int>>pq;
    // pq.push({cnt[0], 0});
    // int tot = n;
    // while(!pq.empty()){
    //     auto [c, p] = pq.top();
    //     pq.pop();
    //     for(int i = 0;i < c;i++){
    //         res.push_back(tot);
    //     }
    //     tot--;
    //     for(auto s : g[p]){
    //         if(s != fa[p][0]){
    //             pq.push({cnt[s],s});
    //         }
    //     }
    // }
    
    for(int i = 0;i < n;i++){
        cout<<res[i]<<" ";
    }
    cout<<endl;
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