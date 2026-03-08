#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//J.cpp Create time : 2026.03.06 21:20

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    vector<vector<pair<int,int>>>g(n * 2);
    map<int, int>l,r;
    int lp = 0, rp = n;
    for(int i = 0;i < n;i++){
        if(!l.count(a[i] - i))l[a[i] - i] = lp++;
        if(!r.count(a[i] + i))r[a[i] + i] = rp++;
        g[r[a[i] + i]].emplace_back(l[a[i] - i], i);
        g[l[a[i] - i]].emplace_back(r[a[i] + i], i);
    }

    vector<int>vs(n * 2);
    vector<int>get(n * 2);
    vector<pair<int,int>>ans;
    int match = 1;
    auto dfs = [&](auto&&self, int p, int eid)->void
    {
        vs[p] = 1;
        vector<int>e;
        for(auto [s, id] : g[p]){
            if(!vs[s]){
                self(self, s, id);
            }
            if(id != eid && !get[id]){
                e.push_back(id);
                get[id] = 1;
            }
        }
        if(e.size() % 2 == 1){
            if(eid == -1){
                match = 0;
                return;
            }
            else{
                e.push_back(eid);
                get[eid] = 1;
            }
        }
        for(int i = 0;i + 1 < e.size();i += 2){
            
            ans.emplace_back(e[i], e[i + 1]);
        }
        return;
    };

    
    for(int i = 0;i < n * 2;i++){
        if(!vs[i]){
            dfs(dfs, i, -1);
        }
    }
    
    if(match){
        cout << "Yes" << endl;
        for(auto [u, v] : ans){
            cout << u + 1 << " " << v + 1 << "\n";
        }
    }
    else{
        cout << "No" << endl;
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