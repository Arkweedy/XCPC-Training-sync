#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.02 17:15:20

const int N = 1e6 + 10;

struct info{
    int mx = 0;
};

info operator+(const info &a,const info &b){
    info c;
    c.mx = max(a.mx,b.mx);
    return c;
}

#define ln (p<<1)
#define rn (p<<1|1)
struct SegTree{
    info tr[N<<2];
    void modify(int p,int l,int r,int x,int y){
        if(l==r){
            //cout<<l<<' '<<r<<' '<<y<<"#\n";
            tr[p].mx = y;
            return;
        }
        int mid = l+r>>1;
        if(x > mid)modify(rn,mid+1,r,x,y);
        else modify(ln,l,mid,x,y);
        tr[p] = tr[ln] + tr[rn];
    }

    int query(int p,int l,int r,int x,int y){
        if(l > y || r < x)return 0;
        if(l >= x && r <= y){
            return tr[p].mx;
        }
        int mid = l+r>>1;
        return max(query(ln,l,mid,x,y),query(rn,mid+1,r,x,y));
    }

    void init(){
        for(int i=0;i<4*N;i++)tr[i].mx = 0;
    }
}pre,suf;

struct Q{
    char c;
    int v;
}q[N];
vector<int>b;

int id(int x){
    return lower_bound(b.begin(),b.end(),x) - b.begin() + 1;
}

int n,qm,a[N],m;

struct Ba{
    int x,y;
}L[N],R[N];

struct Info{
    int mf = 0,mg = 0,ans = 0;
}tr[N<<2];

Info operator+(const Info &a,const Info &b){
    Info c;
    c.ans = max(a.ans,b.ans);
    c.ans = max(a.mf+b.mg,c.ans);
    c.mf = max(a.mf,b.mf);
    c.mg = max(a.mg,b.mg);
    return c;
}

void modify(int p,int l,int r,int x,Info v){
    if(l == r){
        assert(l==r);
        tr[p] = v;
        //cout<<l<<' '<<r<<' '<<v.mf<<' '<<v.mg<<' '<<v.ans<<endl;
        return;
    }
    int mid = l+r>>1;
    if(x > mid)modify(rn,mid+1,r,x,v);
    else modify(ln,l,mid,x,v);
    tr[p] = tr[ln] + tr[rn];
}

void solve()
{
    cin>>n>>qm;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        b.push_back(a[i]);
    }

    for(int i=1;i<=qm;i++){
        cin>>q[i].c;
        if(q[i].c == '!'){
            cin>>q[i].v;
            b.push_back(q[i].v);
        }
    }
    
    sort(b.begin(),b.end());
    b.erase(unique(b.begin(),b.end()),b.end());

    m = b.size();

    for(int i=1;i<=n;i++)a[i] = id(a[i]);
    for(int i=1;i<=qm;i++)if(q[i].c == '!')q[i].v = id(q[i].v);
    int pos = 1;
    //for(int i=1;i<=n;i++)cout<<a[i]<<" \n"[i==n];

    for(int i=n;i > 1;i--){
        int val = suf.query(1,1,m,a[i]+1,m);
        //cout<<i<<' '<<val<<endl;
        val = max(val + 1,suf.query(1,1,m,a[i],a[i]));
        R[i] = {a[i],suf.query(1,1,m,a[i],a[i])};
        suf.modify(1,1,m,a[i],val);
        modify(1,1,m,a[i],{0,val,0});
    }

    for(int i=1;i<=qm;i++){
        if(q[i].c == '<'){
            pos--;
            auto [x,y] = L[pos];
            pre.modify(1,1,m,x,y);
            modify(1,1,m,x,{y,0,0});
            int val = suf.query(1,1,m,a[pos+1]+1,m);
            val = max(val+1,suf.query(1,1,m,a[pos+1],a[pos+1]));
            R[pos+1] = {a[pos+1],suf.query(1,1,m,a[pos+1],a[pos+1])};
            suf.modify(1,1,m,a[pos+1],val);
            modify(1,1,m,a[pos+1],{0,val,0});
        }else if(q[i].c == '>'){
            pos++;
            auto [x,y] = R[pos];
            suf.modify(1,1,m,x,y);
            modify(1,1,m,x,{0,y,0});

            //cout<<x << ' '<<0<<' '<<y<<endl;
            int val = pre.query(1,1,m,1,a[pos-1]-1);
            
            val = max(val + 1,pre.query(1,1,m,a[pos-1],a[pos-1]));
            L[pos-1] = {a[pos-1],pre.query(1,1,m,a[pos-1],a[pos-1])};
            
            pre.modify(1,1,m,a[pos-1],val);

            // cout<<pos-1<<"?\n";
            // cout<<a[pos-1]<<' '<<val<<endl;
            modify(1,1,m,a[pos-1],{val,0,0});
            //cout<<a[pos-1] << ' '<<val<<' '<<0<<endl;
        }else {
            
            a[pos] = q[i].v;
            int ans = max({tr[1].ans,tr[1].mf,tr[1].mg});
            ans = max(ans,pre.query(1,1,m,1,a[pos]-1) + suf.query(1,1,m,a[pos]+1,m) + 1);
            //cout<<suf.query(1,1,m,a[pos]+1,m)<< "??\n";
            cout<<ans<<'\n';
        }

        
    }
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    while(tt--){
        solve();
    }
    return 0;
}