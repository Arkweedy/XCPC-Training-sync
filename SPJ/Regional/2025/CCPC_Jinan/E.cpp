#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 2e5 + 10,mod = 998244353;

ll mi[N];
int c[N],a[N],n,cur[N];

struct HLD{
    vector<vector<int>>e;
    vector<int> sz,son,seq,dfn;
    vector<ll> g,h;
    int tot;

    ll ans;// 外侧同色子集数量
    ll res;
    ll sum;// 子树内合法连通块数量
    HLD(int n){
        e.resize(n + 1);
        sz.resize(n + 1);
        son.resize(n + 1);
        g.assign(n + 1,0);
        seq.resize(n+1);
        dfn.resize(n+1);
        h.assign(n+1,0);
        tot = 0;
        ans = 0;
        res = 0;
        sum = 0;
    }

    void addEdge(int u,int v){
        e[u].push_back(v);
        e[v].push_back(u);
    }

    void dfs1(int u,int f){
        sz[u] = 1;
        dfn[u] = ++tot;
        seq[dfn[u]] = u;
        for(auto v:e[u]){
            if(v==f)continue;
            dfs1(v,u);
            sz[u] += sz[v];
            if(sz[v] > sz[son[u]])son[u] = v;
        }
    }

    void add(int u){
        ans = (ans - mi[c[a[u]]-cur[a[u]]] + 1) % mod;
        sum = (sum - mi[cur[a[u]]] + 1) % mod;
        cur[a[u]]++;
        ans = (ans + mi[c[a[u]]-cur[a[u]]] -1) % mod;
        sum = (sum + mi[cur[a[u]]] - 1) % mod;
    }

    void sub(int u){
        ans = (ans - mi[c[a[u]]-cur[a[u]]] + 1) % mod;
        sum = (sum - mi[cur[a[u]]] + 1) % mod;
        cur[a[u]]--;
        ans = (ans + mi[c[a[u]]-cur[a[u]]] -1) % mod;
        sum = (sum + mi[cur[a[u]]] - 1) % mod;
    }


    void dfs2(int u,int f,int op){
        for(auto v:e[u]){
            if(v==f || v==son[u])continue;
            dfs2(v,u,0);
        }

        if(son[u]){
            dfs2(son[u],u,1);
        }

        add(u);
        for(auto v:e[u]){
            if(v==f||v==son[u])continue;
            for(int i=dfn[v];i<dfn[v] + sz[v];i++){
                add(seq[i]);
            }
        }

        //cout<<u<<' '<<ans<<' '<<cur[a[u]]<<endl;
        
        ll val = sum;
        for(auto v:e[u]){
            if(v==f)continue;
            val = (val - g[v]) % mod;
            g[u] = (g[u] + g[v]) % mod;
            res = (res + g[v] * g[v] % mod) % mod;
        }
        
        res = (res + 2 * ans % mod * val) % mod;
        
        res = (res - g[u] * g[u] % mod) % mod;

        g[u] =  sum;

        if(!op){
            for(int i=dfn[u];i<dfn[u] + sz[u];i++){
                sub(seq[i]);
            }
        }
        
    }

    void work(int rt = 1){
        dfs1(rt,0);
        for(int i=1;i<=n;i++)ans = (ans + mi[c[i]] - 1) % mod;
        dfs2(rt,0,0);
    }

    
};

void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++)c[i] = cur[i] = 0;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        c[a[i]]++;
    }


    HLD tr(n);
    for(int i=0;i<n-1;i++){
        int u,v;cin>>u>>v;
        tr.addEdge(u,v);
    }
    tr.work();

    ll res = tr.res;
    cout<<(res+mod)%mod<<'\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    mi[0] = 1;
    for(int i=1;i<N;i++)mi[i] = mi[i-1]*2%mod;
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}
