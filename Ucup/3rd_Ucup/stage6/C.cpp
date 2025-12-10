#include<bits/stdc++.h>
#define N 300009
#define ls p<<1
#define rs p<<1|1
#define lowbit(x) ((x)&-(x))
using namespace std;
using ll =long long ;
const ll INF =1e18;
const int mod=998244353;
int n,a[N],b[N],ans[N];
vector<int> e[N];
int d[N];
struct node{int l,r;};
bool operator <(node a,node b){return a.l<b.l;}
vector<node> ve[N];
int tot = 0;
void dfs1(int p,int fa)
{
    // d[p]=d[fa]+1;
    // if(d[p]<=21 && tot < 4999) 
    // {
    //     a[p]=1<<d[p];
    //     ve[p].push_back({0,2*a[p]-1});
    //     tot++;
    // }
    // else if(a[p])
    {
        vector<node> vee;
        for(auto [l,r]:ve[fa]) vee.push_back({l+a[p],r+a[p]});
        vector<node> veee(2*vee.size());
        merge(ve[fa].begin(),ve[fa].end(),vee.begin(),vee.end(),veee.begin());
        for(auto [l,r]:veee)
        {
            if(l>2e6) break;
            int m=ve[p].size();
            if(m)
            {
                m--;
                if(l<=ve[p][m].r+1) 
                {
                    ve[p][m].r=max(ve[p][m].r,r);
                    ve[p][m].r=min(ve[p][m].r,2000000);
                }
                else ve[p].push_back({l,r});
            }
            else ve[p].push_back({l,r});
        }
    }
    assert(ve[p].size()<=500);
    for(auto [l,r]:ve[p]) 
        if(b[p]>=l&&b[p]<=r) ans[p]=1;

    for(auto v:e[p])
    {
        if(v==fa) continue;
        if(!a[v]) swap(ve[p],ve[v]);
        dfs1(v,p);
    }
    if(!a[p])  swap(ve[p],ve[fa]);
    else ve[p].clear(),ve[p].shrink_to_fit(); 

}
void solve()
{
    d[0]=-1;
    cin>>n;
    for(int i=1;i<n;i++)
    {
        int u,v;cin>>u>>v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    queue<int>q;
    q.push(1);
    dep[1] = 1;
    while(!q.empty() && tot < 4999){
        
    }
    dfs1(1,0);
    for(int i=1;i<=n;i++) cout<<a[i]<<' ';
    cout<<'\n';
    for(int i=1;i<=n;i++) cout<<ans[i];

}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    int tt=1;
    //cin>>tt;
    while(tt--) solve();
    return 0;
}