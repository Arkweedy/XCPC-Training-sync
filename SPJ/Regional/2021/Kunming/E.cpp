#include<bits/stdc++.h>

using ll = long long;

using namespace std;

constexpr int N = 1e5 + 10;
int n,a[N],pos[N],len,qq;
struct node{int l,r,id;}q[N];
ll ans[N];
ll sum;
bool operator <(node a,node b)
{
    if(pos[a.l]!=pos[b.l]) return pos[a.l]<pos[b.l];
    return a.r<b.r;
}
int tl[N],tr[N];
void addr(int p)
{
    int g=a[p];
    sum-=tl[g];
    tr[g]--;
}
void addl(int p)
{
    int g=a[p];
    sum-=tr[g];
    tl[g]--;
}
void der(int p)
{
    int g=a[p];
    sum+=tl[g];
    tr[g]++;
}
void del(int p)
{
    int g=a[p];
    sum+=tr[g];
    tl[g]++;
}
void solve()
{
    cin>>n;
    len=sqrt(n);
    for(int i=1;i<=n;i++) pos[i]=(i+len-1)/len;
    for(int i=1;i<=n;i++) cin>>a[i];
    cin>>qq;
    for(int i=1;i<=qq;i++) cin>>q[i].l>>q[i].r,q[i].id=i;
    sort(q+1,q+qq+1);
    int pl=1,pr=0;
    for(int i=1;i<=n;i++) tr[a[i]]++;
    for(int i=1;i<=qq;i++)
    {
        int l=q[i].l,r=q[i].r ,id=q[i].id;
        while(pr<r) addr(++pr);
        while(pl>l) addl(--pl);
        while(pr>r) der(pr--);
        while(pl<l) del(pl++);
        ans[id]=1ll*l*(n-r+1)-sum;
    }
    for(int i=1;i<=qq;i++) cout<<ans[i]<<'\n';
    
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tt = 1;
   // cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}