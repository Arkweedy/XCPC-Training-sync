#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//B.cpp Create time : 2026.01.30 05:34

struct EBCC {
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<int> stk;
    std::vector<int> dfn, low, bel;
    int cur, cnt;
    
    EBCC() {}
    EBCC(int n) {
        init(n);
    }
    
    void init(int n) {
        this->n = n;
        adj.assign(n, {});
        dfn.assign(n, -1);
        low.resize(n);
        bel.assign(n, -1);
        stk.clear();
        cur = cnt = 0;
    }
    
    void add(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    void dfs(int x, int p) {
        dfn[x] = low[x] = cur++;
        stk.push_back(x);
        int num=0;
        for (auto y : adj[x]) {
            if (y == p) {
                if(!num) num++;
                else low[x]=std::min(low[x],dfn[p]);
                continue;
            }
            if (dfn[y] == -1) {
                dfs(y, x);
                low[x] = std::min(low[x], low[y]);
            } else if (bel[y] == -1 && dfn[y] < dfn[x]) {
                low[x] = std::min(low[x], dfn[y]);
            }
        }
        
        if (dfn[x] == low[x]) {
            int y;
            do {
                y = stk.back();
                bel[y] = cnt;
                stk.pop_back();
            } while (y != x);
            cnt++;
        }
    }
    std::vector<int> build() {
        for(int i=0;i<n;i++)
            if(dfn[i]==-1) dfs(i,-1);
        return bel;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    auto sa = a;
    sort(sa.begin(),sa.end());
    sa.erase(unique(sa.begin(),sa.end()), sa.end());
    int k = sa.size();
    for(int i = 0;i < n;i++){
        a[i] = lower_bound(sa.begin(),sa.end(), a[i]) - sa.begin();
    }
    EBCC ebcc(n);
    map<pair<int,int>,vector<int>>mp;
    for(int i = 0;i < m;i++){
        int u, v;
        cin >> u >> v;
        u--,v--;
        if(u > v)swap(u, v);
        ebcc.add(u, v);
        mp[make_pair(u,v)].push_back(i);
    }

    ebcc.build();
    
    //build a tree
    auto &bel = ebcc.bel;
    int cnt = ebcc.cnt;
    //iota(bel.begin(),bel.end(), 0);

    vector<vector<pair<int,int>>>g(cnt);
    vector<int>iscut(m);
    vector<vector<int>>e(m);
    int tt = 0;
    for(auto [pr, vec] : mp){
        auto [u, v] = pr;
        if(bel[u] != bel[v]){
            g[bel[u]].emplace_back(bel[v], tt);
            g[bel[v]].emplace_back(bel[u], tt);
            for(auto x : vec){
                iscut[x] = 1;
            }
        }
        e[tt] = vec;
        tt++;
    }

    vector<vector<int>>val(cnt);
    vector<int>w(cnt);
    for(int i = 0;i < n;i++){
        val[bel[i]].push_back(a[i]);
        w[bel[i]]++;
    }

    //dsu on tree
    vector<int>roots;
    vector<int>sz = w;
    vector<int>hson(cnt, -1),fa(cnt, -1), hid(cnt, -1), vs(cnt);
    auto dfs1 = [&](auto&&self, int p)->void
    {
        vs[p] = 1;
        for(auto [s, id] : g[p]){
            if(s != fa[p]){
                fa[s] = p;
                self(self, s);
                sz[p] += sz[s];
                if(hson[p] == -1 || sz[s] > sz[hson[p]]) {
                    hson[p] = s;
                    hid[p] = id;
                }
            }
        }
        return;
    };

    for(int i = 0;i < cnt;i++){
        if(!vs[i]){
            dfs1(dfs1, i);
            roots.push_back(i);
        }
    }
    
    vector<int>ans(m + 1);
    vector<int>c(k), cr(k);
    vector<int>cc(n + 2), ccr(n + 2);
    cc[0] = ccr[0] = k;
    int pc = 0, pcr = 0;
    int all = 0;

    
    auto apply = [&](int p, int eid, int x, int calc)->void
    {
        for(auto v : val[p]){
            cc[c[v]]--;
            ccr[cr[v]]--;
            c[v] += x;
            cr[v] -= x;
            cc[c[v]]++;
            ccr[cr[v]]++;
            if(x == 1){
                while(cc[pc + 1])pc++;
                while(!ccr[pcr])pcr--;
            }
            else{
                while(!cc[pc])pc--;
                while(ccr[pcr + 1])pcr++;
            }
        }
        if(calc){
            if(eid < m){
                for(auto x : e[eid])
                    ans[x] = pc + pcr - all;
            }
            else{
                //assert(pc + pcr == all);
                ans[eid] += pc + pcr;
            }
        }
        return;
    };

    auto apply2 = [&](int p, int x)->void
    {
        for(auto v : val[p]){
            ccr[cr[v]]--;
            cr[v] -= x;
            ccr[cr[v]]++;
            if(x == 1){
                while(!ccr[pcr])pcr--;
            }
            else{
                while(ccr[pcr + 1])pcr++;
            }
        }
        all = pcr;
        return;
    };

    auto dfs3 = [&](auto&&self, int p, int x)->void
    {
        for(auto [s, id] : g[p]){
            if(s != fa[p] ){
                self(self, s, x);
            }
        }
        apply2(p, x);
        return;
    };

    auto addsub = [&](auto&&self, int p, int x)->void
    {
        for(auto [s, id] : g[p]){
            if(s != fa[p]) self(self, s, x);
        }
        apply(p, m, x, 0);
    };


    auto dfs2 = [&](auto&&self, int p,int eid, int keep)->void
    {
        for(auto [s, id] : g[p]){
            if(s != fa[p] && s != hson[p]){
                self(self, s, id, 0);
            }
        }
        if(hson[p] != -1){
            self(self, hson[p], hid[p], 1);
        }
        for(auto [s, id] : g[p]){
            if(s != fa[p] && s != hson[p]){
                addsub(addsub, s, 1);
            }
        }
        apply(p, eid, 1, 1);
        if(!keep){
            addsub(addsub, p, -1);
        }
        return;
    };

    for(auto root : roots){
        dfs3(dfs3, root, -1);
        dfs2(dfs2, root, m, 0);
        dfs3(dfs3, root, 1);
        //assert(pc == 0);
        //assert(pcr == 0);
    }

    for(int i = 0;i < m;i++){
        cout << ans[i] + ans[m] << " \n"[i == m - 1];
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