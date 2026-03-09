#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//2134D.cpp Create time : 2026.02.18 22:30

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>>g(n);
    for(int i = 0;i < n - 1;i++){
        int u, v;
        cin >> u >> v;
        u--,v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int>fa(n);
    auto find = [&](int p)->int
    {
        fa[p] = -1;
        queue<int>q;
        q.push(p);
        int la = -1;
        while(!q.empty()){
            int u = q.front();
            q.pop();
            la = u;
            for(auto s : g[u]){
                if(s != fa[u]){
                    fa[s] = u;
                    q.push(s);
                }
            }
        }
        return la;
    };

    int a = find(0);
    int b = find(a);
    vector<int>list;
    list.push_back(b);
    int p = b;
    while(p != a){
        p = fa[p];
        list.push_back(p);
    }
    int len = list.size();
    if(len == n){
        cout << -1 << endl;
    }
    else{
        for(auto s : list){
            if(g[s].size() > 2){
                for(auto x : g[s]){
                    if(std::find(list.begin(),list.end(), x) == list.end()){
                        cout << fa[fa[x]] + 1 << " " << fa[x] + 1 << " " << x + 1 << endl;
                        return;
                    }
                }
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