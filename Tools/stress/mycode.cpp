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

    auto dfs = [&](auto&&self, int p, int eid)->int
    {
        vs[p] = 1;
        vector<int>buf;
        for(auto [s, id] : g[p]){
            if(!vs[s]){
                if(self(self, s, id))buf.push_back(id);
            }
            else if(id != eid && !get[id]){
                buf.push_back(id);
            }
        }
        for(int i = 0;i + 1 < buf.size();i += 2){
            ans.emplace_back(buf[i], buf[i + 1]);
            get[buf[i]] = get[buf[i + 1]] = 1;
        }
        if(buf.size() % 2 == 0)return 1;
        else{
            ans.emplace_back(eid, buf.back());
            get[buf.back()] = get[eid] = 1;
            return 0;
        }
    };

    int match = 1;
    for(int i = 0;i < n * 2;i++){
        if(!vs[i]){
            int ok = dfs(dfs, i, -1);
            if(!ok){
                match = 0;
                break;
            }
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