#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

const int mod = 998244353;

int qmi(ll a,ll k){
    ll res = 1;
    while(k){
        if(k&1)res=res*a%mod;
        k>>=1;
        a=a*a%mod;
    }
    return res;
}

const int g  =3;
vector<int>Omega(int L){
    int wn = qmi(g,mod/L);
    vector<int>w(L);
    w[L>>1] = 1;
    for(int i=L/2+1;i<=L-1;i++)w[i] = 1ll * w[i-1] * wn%mod;
    for(int i=L/2-1;i;i--)w[i] = w[i<<1];
    return w;
}

auto W = Omega(1<<21);

void DIF(int *a,int n){
    for(int k=n>>1;k;k>>=1){
        for(int i=0,y;i<n;i+=k<<1)
            for(int j=0;j<k;j++){
                y = a[i+j+k],
                a[i+j+k]= 1ll * (a[i+j]-y+mod)*W[k+j]%mod,
                a[i+j] = (y+a[i+j])%mod;
            }
    }
}

void IDIT(int *a,int n){
    for(int k=1;k<n;k<<=1){
        for(int i=0,x,y;i<n;i+=k<<1){
            for(int j=0;j<k;j++){
                x = a[i+j],y = (1ll*a[i+j+k]*W[k+j])%mod,
                a[i+j+k] = x-y<0?x-y+mod:x-y,
                a[i+j] = (y+a[i+j])%mod;
            }
        }
    }
    int Inv = mod - (mod-1)/n;
    for(int i=0;i<n;i++)a[i] = 1ll * a[i] * Inv %mod;
    reverse(a+1,a+n);
}

using Poly = vector<int>;

void DFT(Poly &a){
    DIF(a.data(),a.size());
}

void IDFT(Poly& a){
    IDIT(a.data(),a.size());
}

int norm(int n){
    return 1 << (32-__builtin_clz(n-1));
}

void norm(Poly &a){
    if(!a.empty())a.resize(norm(a.size()),0);
}

Poly &dot(Poly&a,Poly&b){
    for(int i=0;i<a.size();i++)a[i] = 1ll * a[i] * b[i] %mod;
    return a;
}

Poly operator *(Poly a,Poly b){
    int n = a.size() + b.size() - 1,L = norm(n);
    if(a.size() <= 8 || b.size() <= 8){
        Poly c(n);
        for(int i=0;i<a.size();i++)
            for(int j=0;j<b.size();j++)
                c[i+j] = (c[i+j] + (ll)a[i] * b[j])%mod;
        return c;
    }
    a.resize(L),b.resize(L);
    DFT(a),DFT(b),dot(a,b),IDFT(a);
    return a.resize(n),a;
}

const int N = 1e5+10;
int n,a[N],st[N];

ll fact[N],infact[N];

ll c(int a,int b){
    if(b < 0 || a<b)return 0;
    return fact[a] * infact[b] %mod *infact[a-b]%mod;
}

Poly F[N];

Poly CDQ(int l,int r){
    if(l==r)return F[l];
    int mid = l+r>>1;
    return CDQ(l,mid) * CDQ(mid+1,r);
}

void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    int tot = 0;
    for(int i=1;i<=n;i++){
        if(st[i])continue;
        int p = i;
        tot++;
        int len = 0;
        do{
            len++;
            st[p] = 1;
            p = a[p];
        }while(!st[p]);
        F[tot].resize(len,0);
        for(int i=0;i<len;i++)F[tot][i] = c(len,i);
    }
    auto res = CDQ(1,tot);
    ll ans = 0;
    for(int i=0;i<res.size();i++){
        if(i&1)ans = (ans - fact[n-i] * res[i] % mod + mod)%mod;
        else ans = (ans + fact[n-i] * res[i])%mod;
    }
    cout<<(ans+mod)%mod;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    fact[0] = infact[0] = 1;
    for(int i=1;i<N;i++){
        fact[i] = fact[i-1] * i%mod;
        infact[i] = qmi(fact[i],mod-2);
    }
    while(tt--){
        solve();
    }
    return 0;
}