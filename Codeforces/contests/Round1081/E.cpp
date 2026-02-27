#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//E.cpp Create time : 2026.02.21 23:45

// a, b have same cnt element

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n), b(n);
    vector<int>cnt(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
        a[i]--;
        cnt[a[i]]++;
    }
    for(int i = 0;i < n;i++){
        cin >> b[i];
        b[i]--;
        cnt[b[i]]++;
    }
    int ok = 1;
    for(int i = 0;i < n;i++){
        if(cnt[i] % 2 != 0){
            ok = 0;
            break;
        }
    }
    if(!ok){
        cout << -1 << endl;
        return;
    }

    vector<vector<pair<int,int>>>g(n);
    for(int i = 0;i < n;i++){
        g[a[i]].push_back({b[i], i + 1});
        g[b[i]].push_back({a[i], - i - 1});
    }

    // mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    // for(int i = 0;i < n;i++){
    //     shuffle(g[i].begin(),g[i].end(), rng);
    // }

    vector<int>cur(n, 0);
    vector<int>ans(n + 1);
    vector<int>walk(n + 1);

    auto dfs = [&](auto&&self, int p)->void
    {
        for(auto &i = cur[p];i < g[p].size();){
            auto [s, id] = g[p][i];
            i++;
            if(walk[abs(id)])continue;
            walk[abs(id)] = 1;
            if(id > 0)ans[id] = 1;
            self(self, s);
        }
        return;
    };

    for(int i = 0;i < n;i++){
        while(cur[i] < g[i].size()){
            dfs(dfs, i);
        }
    }

    int res = count(ans.begin(),ans.end(), 1);
    cout << res << "\n";
    for(int i = 1;i <= n;i++){
        if(ans[i]){
            cout << i << " ";
        }
    }
    cout << endl;
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