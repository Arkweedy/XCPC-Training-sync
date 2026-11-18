#include<bits/stdc++.h>

using ll = long long;
using i64 = long long;

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

constexpr int N = 2e5 + 1000;

struct Node{
    int s[2], tag, fa, sum, key;
}tr[N];


#define LS(x) tr[(x)].s[0]
#define RS(x) tr[(x)].s[1]
#define fa(x) tr[(x)].fa
#define ls p<<1
#define rs p<<1|1

bool get(int x){return x == RS(fa(x));}
bool isroot(int x){return LS(fa(x)) != x && RS(fa(x)) != x;}

void push_up(int x){tr[x].sum = tr[x].key ^ tr[LS(x)].sum ^ tr[RS(x)].sum;}

void push_down(int x)
{
    if(tr[x].tag){
        swap(LS(x),RS(x));
        tr[LS(x)].tag ^= 1;
        tr[RS(x)].tag^=1;
        tr[x].tag=0;
    }
}

void update(int x){
    if(!isroot(x)) update(fa(x));
    push_down(x);
}

void rotate(int x){
    int y=fa(x),z=fa(y),c=get(x);
    if(!isroot(y))tr[z].s[get(y)] = x;
    fa(tr[x].s[c^1])= y;
    tr[y].s[c] = tr[x].s[c^1];
    tr[x].s[c^1] = y;
    fa(y)= x;
    fa(x) = z;
    push_up(y);
    push_up(x);
}


void splay(int x)
{
    update(x);
    for(int f = fa(x); f = fa(x), !isroot(x); rotate(x))
        if(!isroot(f)) rotate(get(f) == get(x) ? f : x);
}

void access(int x)
{
    for(int p = 0;x;p = x, x= fa(x))splay(x),RS(x) = p, push_up(x);
}

void makeroot(int x)
{
    access(x);
    splay(x);
    tr[x].tag ^= 1;
}

int find(int x)
{
    access(x);
    splay(x);
    while(push_down(x), LS(x))x = LS(x);
    return splay(x), x;
}

void split(int x, int y)
{
    makeroot(x);
    access(y);
    splay(y);
}

void link(int x, int y)
{
    makeroot(x);
    if(find(y) != x){
        fa(x) = y;
    }
}

void cut(int x, int y)
{
    makeroot(x);
    if(find(y) == x && fa(y) == x && !(LS(y)))fa(y) = RS(x) = 0;
}

bool que(int x, int y)
{
    makeroot(x);
    return find(y) == x;
}

void clear(int l,int r){
    Node t={};
    for(int i=l;i<=r;i++) tr[i]=t;
}

int n, m;



int u[N],v[N],nu[N],nv[N];
int d[N],tot[N];
int pr[N];
int gg[N];
int tag[N<<2],mi[N<<2],num[N<<2];
pair<int,int>  push_up1(int p){
    pair<int,int> ans;
    if(mi[ls]<mi[rs]) ans={mi[ls],num[ls]};
    else if(mi[ls]>mi[rs]) ans={mi[rs],num[rs]};
    else ans={mi[ls],num[ls]+num[rs]};
    return ans;
}
void add_tag(int p,int k){
    mi[p]+=k;
    tag[p]+=k;
}
void push_down1(int p){
    if(tag[p]){
        add_tag(ls,tag[p]);
        add_tag(rs,tag[p]);
        tag[p]=0;
    }
}
void build(int p,int l,int r ){
    tag[p]=0;
    if(l==r){
        mi[p]=gg[l];
        num[p]=1; 
    
        return ;
    }
    int m=l+r>>1;
    build(ls,l,m);build(rs,m+1,r);
    auto [a,b]=push_up1(p);
    mi[p]=a,num[p]=b;
    
}
pair<int,int>  query(int p,int l,int r,int jl,int jr ){
    if(jr<jl) return {100000000,1};
    if(jl<=l&&r<=jr) return {mi[p],num[p]};
    int m=l+r>>1;
    push_down1(p);
    if(jr<=m) return  query(ls,l,m,jl,jr);
    if(jl>m) return query(rs,m+1,r,jl,jr);
    auto [mi,num]=query(ls,l,m,jl,jr);
    auto [mii,numm]=query(rs,m+1,r,jl,jr);

    if(mi<mii) return {mi,num};
    if(mi>mii) return {mii,numm};
    return {mi,num+numm};
}
void update(int p,int l,int r,int jl,int jr,int k){
    if(jr<jl) return ;
    if(jl<=l&&r<=jr) {add_tag(p,k);return ;}
    int m=l+r>>1;
    push_down1(p);
    if(jl<=m) update(ls,l,m,jl,jr,k);
    if(jr>m) update(rs,m+1,r,jl,jr,k);
    auto [a,b]=push_up1(p);
    mi[p]=a,num[p]=b;
    

}
void solve()
{
    cin>>n>>m;
    //cout<<"LL"<<n<<m<<endl;
    for(int i=1;i<=m;i++) cin>>u[i]>>v[i];
    for(int i=1;i<=n;i++) tot[i]=m+1;
    for(int i=m;i;i--){
        nu[i]=tot[u[i]];
        nv[i]=tot[v[i]];
        tot[u[i]]=tot[v[i]]=i;
    }
    //cout<<nu[1]<<nv[1]<<"NNN"<<endl;
    for(int i=1;i<=n;i++) d[i]=0;
    clear(0,2*max(n,m)+10);
    int j=0;
    for(int i=1;i<=m;i++){

        while(j<m){
            int uu=u[j+1],vv=v[j+1];
            if(d[uu]==2) break;
            if(d[vv]==2) break;
            if(que(uu,vv)) break;
            d[uu]++;d[vv]++;
            link(uu,vv);j++;
        }
        
        pr[i]=j;
    
        cut(u[i],v[i]); 
        d[u[i]]--;d[v[i]]--;
            }

    int cntt=0;
    for(int i=1;i<=n;i++) d[i]=0;
    for(int i=1;i<=m;i++){
        int uu=u[i],vv=v[i];
        d[uu]++;d[vv]++;
        if(d[uu]==1) cntt++;
        if(d[vv]==1) cntt++;
        gg[i]=cntt-i;
    }

    ll ans=0;
    build(1,1,m);
    for(int i=1;i<=m;i++){
        int uu=u[i],vv=v[i];

    
    
        auto [mi,num]=query(1,1,m,i,pr[i]);
    //    cout<<"UU"<<mi<<' '<<num<<endl;
        if(mi==2-i) ans+=num;
    
        update(1,1,m,i,nu[i]-1,-1);
        update(1,1,m,i,nv[i]-1,-1);

    }
    cout<<ans<<'\n';
    

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