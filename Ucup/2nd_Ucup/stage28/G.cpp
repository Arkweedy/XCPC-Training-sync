#include<bits/stdc++.h>
#define ls p<<1
#define rs p<<1|1
using namespace std;

using ll = long long;


constexpr ll INF = 1e9+7;
constexpr int mod = 1e9 + 7;
constexpr int N = 1e5 + 10;
int n,m;
int a[N];
int b[N];
int to[N],w[N];
int tag[N<<2];
struct node{int w,p;}tr[N<<2];
bool operator <(node a,node b)
{
    if(a.w!=b.w) return a.w<b.w;
    return a.p>b.p;
}
void add_tag(int p,int k)
{
    tag[p]+=k;
    tr[p].w+=k;
}
void push_down(int p)
{
    if(tag[p])
    {
        add_tag(ls,tag[p]);
        add_tag(rs,tag[p]);
        tag[p]=0;
    }
}
void update1(int p,int l,int r,int k,int v)
{
    if(l==r)
    {
        tr[p]={v,l};return ;
    }
    int m=l+r>>1;
    push_down(p);
    if(k<=m) update1(ls,l,m,k,v);
    else update1(rs,m+1,r,k,v);
    tr[p]=max(tr[ls],tr[rs]);
}
void update2(int p,int l,int r,int jl,int jr,int k)
{
    if(jl>jr) return ;
    if(jl<=l&&r<=jr) {add_tag(p,k);return ;}
    int m=l+r>>1;
    push_down(p);
    if(jl<=m) update2(ls,l,m,jl,jr,k);
    if(jr>m) update2(rs,m+1,r,jl,jr,k);
    tr[p]=max(tr[ls],tr[rs]);
}
void solve()
{
    to[0]=-1;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    sort(b+1,b+n+1);
    for(int i=1;i<=n;i++) b[i]+=b[i-1],b[i]=min(b[i],m+1);
    a[++n]=m;
    for(int i=1;i<n;i++) to[i]=-1;
    for(int i=1;i<n;i++)
    {
        int p=upper_bound(a+1,a+n+1,b[i])-a;
        if(p<=n) to[i]=p-1,w[i]=a[p]-b[i];
    }
    for(int i=1;i<=(n+2)<<2;i++) tr[i]={-INF,0},tag[i]=0;
    int ans=0;
    stack<node> st;
    int cnt=0;
    for(int i=n-1;i;i--)
    {
        int t=to[i];
       // cerr<<i<<' '<<t<<endl;
        if(t==-1) continue;
        if(!cnt) 
        {
            //cerr<<i<<' '<<a[i+1]-a[i]<<endl;
            for(int i=t+1;i<n;i++) update1(1,0,n,i,a[i+1]-a[i]);
        }
        cnt=1;
        int spe=0;
        if(to[i]!=to[i-1]) spe=1;
        if(spe)
        {
            update1(1,0,n,t,w[i]);
        }
        node no=tr[1];
        if(no.w>0)
        {
            ans+=no.w;
           // cerr<<i<<' '<<no.w<<' '<<no.p<<endl;
            update1(1,0,n,no.p,-INF);
            while(st.size()&&st.top().p<=no.p)
            {
                auto no=st.top();
                update2(1,0,n,no.p,n,-no.w);
                st.pop();
            }
        }
        if(spe&&no.w>0)
        {
            if(no.p==t)
            {
                update1(1,0,n,t,0);
                update2(1,0,n,t,n,a[t+1]-a[t]-w[i]);
                st.push({a[t+1]-a[t]-w[i],t});
            }
            else 
            {
                update1(1,0,n,t,a[t+1]-a[t]);
            }
        }
    }
    cout<<ans<<'\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}