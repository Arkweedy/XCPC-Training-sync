#include<bits/stdc++.h>

using namespace std;

using ll = long long;

constexpr int N = 1e6 + 10;

int n,m;
int f[N],st[N]ed[N];
ll a[N],l[N],r[N];

struct edge{
    int u,v;
    ll w;
}e[N];

int find(int x){
    if(f[x]!=x)f[x] = find(f[x]);
    return f[x];
}

void merge(int u,int v)
{
    u = find(u),v= find(v);
    f[v] = u;
    r[u] = max(r[u],r[v]);
    l[u] = min(l[u],l[v]);
}
void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    ll res = 0;
    for(int i=0;i<n-1;i++){
        cin>>e[i].u>>e[i].v;
    }
    m = n - 1;
    
    for(int i=0;i<(1<<m);i++){
        ll ans = 0;
        for(int i=1;i<=n;i++)f[i] = i,l[i] = r[i] = a[i];
        memset(st,0,sizeof st);
        for(int j=0;j<m;j++){
            if(i>>j&1)merge(e[j].u,e[j].v);
        }
        for(int i=1;i<=n;i++){
            if(st[find(i)])continue;
            st[find(i)] = 1;
            ans += r[find(i)] - l[find(i)];
        }
        res = max(res,ans);
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
