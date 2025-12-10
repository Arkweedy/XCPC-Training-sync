#include<bits/stdc++.h>
using ll = long long;
using namespace std;

constexpr int N = 1e5 + 10,mod = 998244353;
constexpr ll inf = 1e18;
int a[N],n,m,q,b[N],id[N],deg[N],tot;

ll dp[N];
vector<pair<int,int>>e[N],to[N];

struct PQ{
    priority_queue<ll>A,B;
    ll top(){
        while(!B.empty() && A.top() == B.top()){
            A.pop();
            B.pop();
        }
        return -A.top();
    }

    void pop(ll x){
        B.push(-x);
    }
    void push(ll x){
        if(!B.empty() && B.top() == -x){
            B.pop();
        }
        else{
            A.push(-x);
        }
    }
}pq[N];

void solve()
{
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++)cin>>a[i];
    int B = sqrt(m*log(m));
    while(m--){
        int u,v,w;cin>>u>>v>>w;
        e[u].push_back({v,w});
        e[v].push_back({u,w});
        deg[u]++,deg[v]++;
    }

    for(int i=1;i<=q;i++)cin>>b[i];

    for(int i=1;i<=n;i++){
        int u = i;
        if(deg[u]>B){
            id[u] = ++tot;
            for(auto [v,w]:e[u]){
                to[v].push_back({u,w});
                pq[tot].push(w);
            }
        }
    }

    for(int i=q;i;i--){
        int u = b[i];
        ll pre = dp[u];
        if(deg[u] <= B){
            dp[u] = inf;
            for(auto [v,w]:e[u])dp[u] = min(dp[u],dp[v]+w);
        }else{
            dp[u] = pq[id[u]].top();
            //cout<<i<<' '<<u<<' '<<dp[u]<<endl;
        }
        for(auto [v,w]:to[u])pq[id[v]].pop(pre + w),pq[id[v]].push(w + dp[u]);

        
    }

    ll res = 0;
    for(int i=1;i<=n;i++)res = (res + dp[i] % mod * a[i] % mod)%mod;

    cout<<res<<'\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    while (tt--)
    {
        solve();
    }
    return 0;    
}
