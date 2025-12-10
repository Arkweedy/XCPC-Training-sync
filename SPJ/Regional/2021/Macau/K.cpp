#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e5 + 10;
int n,m;
int fa[N];
int find(int p)
{
    if(fa[p]!=p) fa[p]=find(fa[p]);
    return fa[p];
}
pair<int,int> e[N];
struct node{int v,w;};
vector<node> te[N];
int ans=0;
int d[N];
void sol()
{
    ans=1;
    queue<int > q;
    for(int i=1;i<=n;i++)
        if(d[i]==1) q.push(i);
    while(q.size())
    {
        int p=q.front();q.pop();
        for(auto [v,i]:te[p]) 
        {
            d[v]--;
            if(d[v]==1) q.push(v);
        }
    }
    //for(int i=1;i<=n;i++) cout<<d[i]<<endl;
}
void solve()
{
    ans=0;
    cin>>n>>m;
    int g;
    for(int i=1;i<=m;i++) cin>>e[i].first>>e[i].second;
    for(int i=1;i<=n;i++) d[i]=0,te[i].clear();
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1;i<=m;i++)
    {
        int u=e[i].first,v=e[i].second;
        int uu=find(u),vv=find(v);
        if(uu==vv)
        {
            te[u].push_back({v,i});
            te[v].push_back({u,i});
            d[u]++;d[v]++;
            sol();
            g=i;
            break;
        }
        fa[uu]=vv;
        te[u].push_back({v,i});
        te[v].push_back({u,i});
        d[u]++;d[v]++;
    }
    if(!ans) cout<<-1<<'\n';
    else 
    {
        for(int i=1;i<=g;i++)
        {
            int u=e[i].first,v=e[i].second;
            if(d[u]==2&&d[v]==2) cout<<i<<" \n"[i==g];
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;

}