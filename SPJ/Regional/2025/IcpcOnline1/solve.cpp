#include<bits/stdc++.h>

using namespace std;

using ll = long long;

constexpr int N = 2e6 + 10;
constexpr ll INF=1e18;
int n,m;
int vis[N];
ll a[N],dp[N][2];

vector<pair<int,int>>e[N];

void add(int u,int v,int w){
    e[v].push_back({u,w});
    e[u].push_back({v,w});
}

void dfs(int u,int val,int f){
    vis[u] = 1;
    dp[u][1] = val;
    ll g=0;
    for(auto [v,w]:e[u]){
        if(v==f)continue;
        //cout<<v<<' '<<u<<' '<<w<<endl;
        dfs(v,w,u);
        g=max(g,dp[v][1]-dp[v][0]);
        dp[u][1] += dp[v][0];
    }

    dp[u][0]=dp[u][1]-val+g;
}

void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    ll res = 0;
    for(int i=0;i<n-1;i++){
        int u,v;cin>>u>>v;
        int w = abs(a[u]-a[v]);
        if(a[u] == a[v])continue;
        else if(a[u] > a[v]){
            add(2*v,2*u-1,w);
        }
        else{
            add(2*u,2*v-1,w);
        }
    }

    for(int i=1;i<=n;i++){
        add(2*i-1,2*i,0);
    }

    for(int i=1;i<=2*n;i++){
        if(!vis[i]){
            dfs(i,0,0);
            res += max(dp[i][0],dp[i][1]);
        }
    }

    cout<<res<<'\n';
}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int t = 1;
  //  cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
