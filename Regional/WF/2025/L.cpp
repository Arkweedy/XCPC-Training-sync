#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;
constexpr int N =1e5+10;
//Create time: 2025.12.25 13:43:35
int n,x,y,yy;
struct node{int l,r;}p[N];
bool operator <(node a,node b){return a.l<b.l;}
void solve()
{
    cin>>n>>x>>y>>x>>yy;
    if(y<yy) { cout<<0;return ;}
    swap(y,yy);
    int ans=yy-y;
    for(int i=1;i<=n;i++) cin>>x>>p[i].l>>x>>p[i].r;
    for(int i=1;i<=n;i++) p[i].l=max(p[i].l,y),p[i].r=min(p[i].r,yy);
    sort(p+1,p+n+1);
    int pl=y,pr=y;
    for(int i=1;i<=n;i++)
    {
        if(p[i].l>p[i].r) continue;
        if(p[i].l>pr)
        {
            ans-=pr-pl;
            pl=p[i].l,pr=p[i].r;
        }
        else pr=max(pr,p[i].r);
    
    }
    ans-=pr-pl;
    cout<<ans;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}