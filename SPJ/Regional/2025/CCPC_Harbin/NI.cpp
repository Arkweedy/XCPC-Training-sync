#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e5 + 10;
constexpr int P = 1e9 + 7;
struct node{int x,y,z;};
bool operator <(node a,node b)
{
    if(a.x!=b.x) return a.x<b.x;
    if(a.y!=b.y) return a.y<b.y;
    return a.z<b.z;
}
map<node,int> mp;
int n,m;
map<int,int> mx,my,mz;
void solve()
{
    mp.clear();
    mx.clear();my.clear();mz.clear();
    cin>>n>>m;
    for(int i=1;i<=n+m;i++)
    {
        int u,v,w;cin>>u>>v>>w;
        mp[{u,v,w}]^=1;
    }
    for(auto [no,id]:mp)
    {
        if(id==0) continue;
        auto [u,v,w]=no;
        mx[u]^=1;
        my[v]^=1;
        mz[w]^=1;
        //    cout<<u<<' '<<v<<' '<<w<<endl;
    }
    int err=0;
    for(auto [id,w]:mx) 
        if(w) err=1;
    for(auto [id,w]:my) 
        if(w) err=1;
    for(auto [id,w]:mz) 
        if(w) err=1;
    if(err) cout<<"NO\n";
    else cout<<"YES\n";
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}