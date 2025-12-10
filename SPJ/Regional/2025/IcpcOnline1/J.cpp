#include<bits/stdc++.h>
#define int long long
using namespace std;

using ll = long long;

constexpr int N = 2e6 + 10,M = 5e5;//offset

constexpr int mod = 998244353;

int n ,m ,k;

ll f[N][51];//f(l,len)
ll comb[N];
ll x[N];
ll qmi(ll a,ll k){
    ll res = 1;
    while(k){
        if(k&1)res = res * a%mod;
        k>>=1;
        a=a*a%mod;
    }
    return res;
}
ll fact[N],infact[N];
ll c(int a,int b){
    if(b <0 || a<b)return 0;
   return fact[a] * infact[b] %mod*infact[a-b]%mod;
}

ll cs(int l,int r){
    l = max(0ll,l);
    r = min(m,r);
    if(l>r)return 0;
    if(l==0)return comb[r];
    else return (comb[r]-comb[l-1] + mod)%mod;
}

ll fceil(ll n,ll m){
    if(n>=0)return (n+m-1)/m;
    else return n/m;
}

ll ffloor(ll n,ll m){
    if(n>=0)return n/m;
    else return (n-m+1)/m;
}

ll get(int l,int len){
    int s  =l,t = l + len;
    l += M;
    if(f[l][len] == -1){
        f[l][len] = 1;
        for(int i=1;i<=n;i++){
            ll L = fceil(s+m-x[i],2);
            ll R = ffloor(t+m-x[i],2);
            f[l][len] = f[l][len] * cs(L,R) % mod;
            //cout<<cs(L,R)<<"#\n";
        }
        //cout<<l<<' '<<len<<' '<<f[l][len]<<endl;
    }
    return f[l][len];
}

ll calc()
{
    for(int i=0;i<N;i++){
        for(int j=0;j<=50;j++)f[i][j] = -1;
    }
    ll res = 0;
    // x sorted
    for(int i=x[1]-m;i<=x[1]+m;i++){
        for(int len=0;len<=k;len++){
            int j = i + len;
            for(int s=i;s<=j;s++){
                for(int t=s;t<=j;t++){
                    ll op = (j-i) - (t-s);
                    if(op%2)res = (res -get(s,t-s)+mod)%mod;
                    else res = (res + get(s,t-s))%mod;
                }
            }
        }
    }
    return res;
}

void solve()
{

    cin>>n>>m>>k;
    for(int i=0;i<=m;i++){
        comb[i] = c(m,i);
    }
    for(int i=1;i<=m;i++){
        comb[i] = (comb[i] + comb[i-1])%mod;
    }

    vector<int>a(n),b(n);
    for(int i = 0;i < n;i++){
        int u,v;
        cin>>u>>v;
        a[i] = u + v;
        b[i] = u - v;
    }
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());

    ll ans1 = 0,ans2 = 0;
    for(int i=0;i<n;i++){
        x[i+1] = a[i];
        //cout<<a[i]<<' ';
    }
    ans1 = calc();
    for(int i=0;i<n;i++){
        x[i+1] = b[i];
    }
    ans2 = calc();
    //cout<<ans1<<' '<<ans2<<endl;
    cout<<ans1*ans2%mod;
}

signed main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    fact[0] = infact[0] = 1;
    for(int i=1;i<N;i++){
        fact[i] = i * fact[i-1]%mod;
        infact[i] = qmi(fact[i],mod-2);
    }
    int t = 1;
    while(t--){
        solve();
    }
    return 0;
}
