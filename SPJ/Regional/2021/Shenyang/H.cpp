#include<bits/stdc++.h>

using ll = long long;

using namespace std;

constexpr int N = 1e5 + 10;

struct EBCC{
    int n;
    vector<vector<int>>adj;
    vector<int>stk;
    vector<int>dfn,low,bel;
    int cur,cnt;

    EBCC(){}
    EBCC(int n){
        init(n);
    }

    void init(int n){
        this->n = n;
        adj.assign(n,{});
        dfn.assign(n,-1);
        low.resize(n);
        bel.assign(n,-1);
        stk.clear();
        cur = cnt = 0;
    }

    void addEdge(int u,int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int x,int p){
        dfn[x] = low[x] = cur++;
        stk.push_back(x);
        for(auto y:adj[x]){
            if(y == p)continue;
            if(dfn[y] == -1){
                dfs(y,x);
                low[x] = min(low[x],low[y]);
            }else if(bel[y] == -1 && dfn[y] < dfn[x]){
                low[x] = min(low[x],dfn[y]);
            }
        }

        if(dfn[x] == low[x]){
            int y;
            do{
                y = stk.back();
                bel[y] = cnt;
                stk.pop_back();
            }while(y!=x);

            cnt++;
        }
    }

    std::vector<int>work(){
        dfs(0,-1);
        return bel;
    }

    
};

void solve()
{
    int n,m;cin>>n>>m;
    map<pair<int,int>,int>ha;
    EBCC g(n);
    ll sum = 0;
    int mi = 1e9;
    for(int i=0;i<m;i++){
        int u,v,w;cin>>u>>v>>w;
        u--,v--;
        sum += w;
        ha[{u,v}] = ha[{v,u}] = w;
        g.addEdge(u,v);
    }
    
    if(m%2==0)cout<<sum<<'\n';
    else{

        auto bel = g.work();

        auto &adj = g.adj;
        int cnt = g.cnt;
        vector<vector<pair<int,int>>>e(cnt);
        vector<int>sz(cnt);

        for(auto [k,w]:ha){
            auto [u,v] = k;
            if(bel[u] == bel[v])mi = min(mi,w);
        }

        for(int i=0;i<n;i++){
            for(auto j:adj[i]){
                if(bel[i] != bel[j]){
                    e[bel[i]].push_back({bel[j],ha[{i,j}]});
            
                }else{
                    sz[bel[i]]++;
                }
            }
        }

        auto dfs = [&](auto &&self,int u,int fa)->void{
            //cout<<sz[u]<<endl;
            sz[u]/=2;
            for(auto [v,w]:e[u]){
                if(v==fa)continue;
                self(self,v,u);
                if(sz[v] % 2 == 0){
                    mi = min(mi,w);
                }
                sz[u] += sz[v] + 1;
            }
            
        };

        dfs(dfs,0,-1);

        cout<<sum-mi<<'\n';
    }


}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    while(tt--){
        solve();
    }
}