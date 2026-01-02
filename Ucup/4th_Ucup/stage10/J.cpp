#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.02 16:18:02

struct Edge{
    int u,v;
};

void solve()
{
    int n,m;cin>>n>>m;
    vector<vector<int>>e(n);
    vector<Edge>edge;
    vector<set<int>>ha(n);

    while(m--){
        int u,v;cin>>u>>v;
        u--,v--;
        edge.push_back({u,v});
        e[u].push_back(v);
        e[v].push_back(u);
        ha[u].insert(v);
        ha[v].insert(u);
    }
    
    vector<int>st(n,15),c(n,-1);

    auto check = [&](int x)->void
    {
        for(auto u:e[x]){
            for(auto v:e[x]){
                if(u == v)continue;
                if(c[u] == -1 || c[v] == -1 || c[v] != c[u])continue;
                if(!ha[u].count(v))continue;
                int mask = 15 ^ (1 << c[v]);
                st[x] &= mask;
            }
        }
    };

    // for(auto [u,v] : edge){
    //     if(c[u] == -1 && c[v] == -1){
    //         check(u),check(v);
            
    //         int x = 0;

    //         set<int>s,t;
    //         for(auto x : e[u])s.insert(x);
    //         for(auto x : e[v])if(s.count(x))t.insert(x);

    //         while(x < 4){
    //             if(!(st[u] >> x & 1)){
    //                 x++;
    //                 continue;
    //             }
    //             if(!(st[v] >> x & 1)){
    //                 x++;
    //                 continue;
    //             }
    //             bool ok = 1;
    //             for(auto y : t)if(c[y] == x)ok = 0;
    //             if(!ok){
    //                 x++;
    //                 continue;
    //             }
    //             break;
    //         }

    //         if(x == 4)continue;
            
    //         c[u] = x,c[v] = x;
    //     }
    // }


    for(int i=0;i<n;i++){
        if(c[i] == -1){
            check(i);
            for(int j=0;j<4;j++){
                if(st[i] >> j & 1){
                    c[i] = j;
                    break;
                }
            }
            assert(c[i] != -1);
        }
        cout<<c[i] + 1 << ' ';
    }
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    while(tt--){
        solve();
    }
    return 0;
}