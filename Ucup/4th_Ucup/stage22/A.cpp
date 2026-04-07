#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using ll = long long;

using namespace std;

//A.cpp Create time : 2026.04.07 14:57

const int N = 2e5 + 10,mod = 998244353;

ll qmi(ll a,ll k){
    ll res  =1;
    while(k){
        if(k&1)res=res*a%mod;
        k>>=1;
        a=a*a%mod;
    }
    return res;
}

int n,k;

ll v[N<<2],tag[N<<2],p[N];

#define ln (p<<1)
#define rn (p<<1|1)

void app(int p,ll x){   
    v[p] = v[p] * x % mod;
    tag[p] = tag[p] * x % mod;
}

void down(int p){
    app(ln,tag[p]);
    app(rn,tag[p]);
    tag[p] = 1;
}

void modify(int p,int l,int r,int x,ll y){
    if(l==r){
        v[p] = y;
        return;
    }
    int mid = l+r>>1;
    down(p);
    if(x>mid)modify(rn,mid+1,r,x,y);
    else modify(ln,l,mid,x,y);
    v[p] = (v[ln] + v[rn]) % mod;
}

void change(int p,int l,int r,int x,int y,ll t){
    if(l>y||r<x)return;
    if(l>=x && r<=y){
        app(p,t);
        //cout<<t<<endl;
        return;
    }
    int mid = l+r>>1;
    down(p);
    change(ln,l,mid,x,y,t);
    change(rn,mid+1,r,x,y,t);
    v[p] = (v[ln] + v[rn]) % mod;
}

ll query(int p,int l,int r,int x,int y){
    if(l>y||r<x)return 0;
    if(l>=x && r<=y){
        return v[p];
    }
    down(p);
    int mid = l+r>>1;
    return (query(ln,l,mid,x,y) + query(rn,mid+1,r,x,y) ) %mod;
}
ll dp[N];

void solve()
{
    for(int i=0;i<4*N;i++)tag[i] = 1;
    cin>>n>>k;
    for(int i=2;i<=n+1;i++){
        ll a,b;cin>>a>>b;
        p[i] = a * qmi(b,mod-2)%mod;
        //cout<<p[i]<<endl;
    }
    modify(1,0,n+1,0,1);
    modify(1,0,n+1,1,1);
    for(int i=2;i<=n+1;i++){
        change(1,0,n+1,i-1,i-1,(1+mod-p[i])%mod);
        change(1,0,n+1,0,i-2,p[i]);
        dp[i] = query(1,0,n+1,i-k,i-1);
        //cout<<dp[i]<<endl;
        modify(1,0,n+1,i,dp[i]);
    }

    cout<<(1-dp[n+1] + mod)%mod;
    
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