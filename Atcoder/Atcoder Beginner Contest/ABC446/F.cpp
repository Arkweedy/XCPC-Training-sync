#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//F.cpp Create time : 2026.02.21 20:37

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>>g(n);
    for(int i = 0;i < m;i++){
        int u, v;
        cin >> u >> v;
        u--,v--;
        g[u].push_back(v);
    }
    vector<int>ans(n);
    vector<int>vs(n);
    vector<int>reach(n);
    reach[0] = 1;
    int tot = 0;
    int nochs = 1;
    queue<int>q;
    for(int i = 0;i < n;i++){
        if(reach[i]){
            vs[i] = 1;
            tot++;
            q.push(i);
            nochs--;
            while(!q.empty()){
                int p = q.front();
                q.pop();
                for(auto s : g[p]){
                    if(reach[s] == 0){
                        reach[s] = 1;
                        nochs++;
                        if(!vs[s] && s <= i){
                            vs[s] = 1;
                            tot++;
                            q.push(s);
                            nochs--;
                        }
                    }
                }
            }
        }
        if(tot == i + 1){
            ans[i] = nochs;
        }
        else{
            ans[i] = -1;
        }
    }

    for(int i = 0;i < n;i++){
        cout << ans[i] << "\n";
    }
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