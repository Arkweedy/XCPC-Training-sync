#include<bits/stdc++.h>

using namespace std;

using ll = long long;


constexpr ll INF = 1e18;
constexpr int mod = 1e9 + 7;
constexpr int N = 1e5 + 10;

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<set<int>>g(n);
    vector<vector<int>>adj(n);
    for(int i = 0;i < n - 1;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        g[u].insert(v);
        g[v].insert(u);
    }

    vector<int>sz(n, 1),hson(n, -1),fa(n, -1),top(n),dep(n),in(n);
    int tot = 0;
    auto dfs1 = [&](auto&&self, int p)->void
    {
        in[p] = ++tot;
        for(auto s : g[p]){
            if(s != fa[p]){
                adj[p].push_back(s);
                fa[s] = p;
                dep[s] = dep[p] + 1;
                self(self, s);
                sz[p] += sz[s];
                if(hson[p] == -1 || sz[hson[p]] < sz[s]){
                    hson[p] = s;
                }
            }
        }
        return;
    } ;

    auto dfs2 = [&](auto&&self, int p)->void
    {
        if(hson[p] != -1){
            top[hson[p]] = top[p];
            self(self, hson[p]);
        }

        for(auto s : g[p]){
            if(s != fa[p] && s != hson[p]){
                top[s] = s;
                self(self, s);
            }
        }
        return;
    };

    auto check = [&](int u,int v)->bool{
        return in[u] <= in[v] && in[v] < in[u] + sz[u];
    };

    auto rootedParent = [&](int u,int v)->int{
        swap(u,v);
        if(u==v)return u;
        if(!check(u,v)){
            return fa[u];
        }
        auto it = upper_bound(adj[u].begin(),adj[u].end(),v,[&](int x,int y){
            return in[x] < in[y];
        }) - 1;
        return *it;
    };

    int root = 0;
    dfs1(dfs1, root);
    dfs2(dfs2, root);

    auto lca = [&](int u, int v)->int
    {
        while(top[u] != top[v]){
            if(dep[top[u]] > dep[top[v]]){
                u = fa[top[u]];
            }
            else{
                v = fa[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    };

    g[0].insert(-1);

    while(q--){
        int k;
        cin>>k;
        vector<int>a(k);
        set<int>ha;

        for(int i = 0;i < k;i++){
            cin>>a[i];
            ha.insert(a[i]);
            a[i]--;
        }


        if(ha.size()!=k){
            cout<<"No\n";
            continue;
        }

        int ok = 1;

        int cur = 0;
        auto check_subtree = [&](auto&&self, int p)->void
        {
            for(int i = 0;i < (int)g[p].size() - 1;i++){//sons cnt
                if(cur == k)return;
                if(g[p].count(a[cur]) && a[cur] != fa[p]){
                    self(self, a[cur++]);
                }
                else{
                    ok = false;
                    return;
                }
            }
            return;
        };
        set<pair<int,int>>s;
        while(1){
            int p = a[cur++];
            if(!s.empty()){
                auto it = s.upper_bound({in[p],n});
                if(it!=s.begin()){
                    it = prev(it);
                    auto [l,r] = (*it);
                    if(r >= in[p]){
                        ok = false;
                    }
                }
            }
            check_subtree(check_subtree, p);
            if(cur == k)break;
            int lc = lca(p, a[cur]);
            if(lc != fa[a[cur]] || lc == p){
                ok = false;
                break;
            }
            auto u = rootedParent(p,lc);
            s.insert({in[u],in[u] + sz[u]-1});
        }

        cout<< (ok ? "Yes\n" : "No\n");
    }
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    //cin>>t;
    while(t--){
        solve();
    }
    return 0;
}