#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//G.cpp Create time : 2026.06.16 02:09

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>>g(n);
    vector<int>in(n);
    for(int i = 0;i < m;i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        in[v]++;
    }
    queue<int>q;
    for(int i = 0;i < n;i++){
        if(in[i] == 0)q.push(i);
    }
    vector<int>len(n);
    while(!q.empty()){
        int p = q.front();
        q.pop();
        for(auto s : g[p]){
            len[s] = max(len[s], len[p] + 1);
            in[s]--;
            if(in[s] == 0){
                q.push(s);
            }
        }
    }
    int ans = 0;
    for(int i = 0;i < n;i++){
        ans = max(ans, len[i]);
    }
    cout << ans << endl;
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