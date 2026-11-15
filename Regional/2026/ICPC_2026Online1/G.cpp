#include <bits/stdc++.h>
#define N 109
#define int unsigned long long 
using ll = long long;
using i64 = long long;
using namespace std;
vector<int> gr[N];
int dp[N][N],dpp[N][N],fr[N],ed[N];
int e[N][N];
int c[N];
int sit[N];
vector<ll> ve[2];
    int st=-1,ma=-1;
i64 C;
vector<vector<pair<int,i64>>>g(N), rg(N), ng(N);
void dfs(int p,ll v,int op){
    
    if(v>C) return ;
    if(sit[p]==st){
        ve[op].push_back(v);
    }
    if(op==0){
        for(auto [vv,ww]:g[p])
        {
            if(sit[vv]==sit[p]+1) dfs(vv,v+c[vv],op);
        }
    }
    else {
for(auto [vv,ww]:rg[p])
        {
            if(sit[vv]==sit[p]-1) dfs(vv,v+c[vv],op);
        }
    }
}
void solve()
{
    int n, m;
    cin >> n >> m;
    
    cin >> C;
    for(int i=1;i<=n;i++) cin>>c[i];
    
    for(int i = 0;i < m;i++){
        int u, v;
        i64 w;
        w=1;
        cin >> u >> v ;
        e[u][v]=1;
        u--,v--;
        g[u].emplace_back(v, w);
        rg[v].emplace_back(u, w);
    }

    constexpr int inf = 1e9;

    auto dij = [&](vector<vector<pair<int,i64>>>&g, int so)->vector<int>
    {
        queue<int>q;
        q.push(so);
        vector<int>dis(n, inf);
        dis[so] = 0;
        while(!q.empty()){
            int p = q.front();
            q.pop();
            for(auto [s, w] : g[p]){
                if(dis[p] + 1 < dis[s]){
                    dis[s] = dis[p] + 1;
                    q.push(s);
                }
            }
        }
        return dis;
    };

    auto dis = dij(g, 0);
    auto rdis = dij(rg, n - 1);

    int ds = dis[n - 1];

    vector<int>ok(n);
    for(int i = 0;i < n;i++){
        if(dis[i] + rdis[i] == ds){
            ok[i] = 1;
        }
    }

    for(int i = 0;i < n;i++){
        for(auto [j, w] : g[i]){
            if(ok[i] && ok[j] && (dis[i] + 1 == dis[j])){
                ng[i].emplace_back(j, w);
            }
        }
    }

    g = move(ng);
    for(int i=0;i<n;i++) 
        if(ok[i]) gr[dis[i]].push_back(i);
    for(int i=0;i<n;i++){
        if(ok[i]==0) sit[i]=-10;
        else sit[i]=dis[i];
    }
    dp[0][0]=1;
    for(int i=1;i<=dis[n-1];i++)
    {
        int b=gr[i].size();
        int ne=gr[i-1].size();
        int sum=0;
        for(int j=0;j<b;j++)
            for(int jj=0;jj<ne;jj++)
            {
                int a=gr[i-1][jj],b=gr[i][j];
                if(e[a][b]) dp[i][j]+=dp[i-1][jj];
            }
        for(int j=0;j<b;j++)fr[i]+=dp[i][j];
        
    }

    dpp[n-1][0]=1;
    for(int i=n-2;i>=0;i--){
        int b=gr[i].size(),ne=gr[i+1].size();
        for(int j=0;j<b;j++)
            for(int jj=0;jj<ne;jj++){
                int a=gr[i][j],b=gr[i+1][jj];
                if(e[a][b]) dpp[i][j]+=dpp[i+1][jj];
            }
        for(int j=0;j<b;j++) ed[i]+=dpp[i][j];
    }



    unsigned long long ans=0;
    for(int i=0;i<n;i++){
        if(fr[i]+ed[i]<ma) st=fr[i]+ed[i],ma=i;
    }



    dfs(0,c[0],0)
    dfs(n-1,c[n-1],1);

    
    sort(ve[0].begin(),ve[0].end());
    sort(ve[1].begin(),ve[1].end());

    int sz1 = ve[0].size(),  sz2 = ve[1].size();
    int p = sz2 - 1;
    for(int i = 0;i < sz1;i++){
        while(ve0[i] + ve1[p] >C){
            p--;
        }
        ans += 
    }
    
    cout<<ans;
    



}

signed  main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}