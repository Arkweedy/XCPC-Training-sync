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

ll calc() {
    ll mn = x[1];
    ll tL = mn - m;
    ll tR = mn + m;

    int W = (int)(tR - tL + 2); // 足够覆盖 s ∈ [tL, tR+1)
    static vector<array<ll, 51>> memo;
    memo.assign(W, {});
    for (int i = 0; i < W; ++i)
        for (int len = 0; len <= 50; ++len)
            memo[i][len] = -1;

    auto get_local = [&](ll s, int len) -> ll {
        if (len < 0) return 0;              // 重要：防止 K=0 时出现负长度
        int idx = (int)(s - tL);
        ll &cell = memo[idx][len];
        if (cell != -1) return cell;
        ll S = s, T = s + len;
        ll prod = 1;
        for (int i = 1; i <= n; ++i) {
            ll a = m + S - x[i];
            ll b = m + T - x[i];
            // L = ceil(a/2), R = floor(b/2)
            ll L = (a >= 0 ? (a + 1) / 2 : -((-a) / 2));
            ll R = (b >= 0 ?  b      / 2 : -(( -b + 1) / 2));
            prod = prod * cs((int)L, (int)R) % mod;
            if (!prod) break;
        }
        cell = prod;
        return cell;
    };

    ll res = 0;
    for (ll t = tL; t <= tR; ++t) {
        ll A = get_local(t,     k);          // F(t, t+K)
        ll B = get_local(t + 1, k - 1);      // F(t+1, t+K)  ← 关键修正
        res += A - B;
        res %= mod;
        if (res < 0) res += mod;
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
    //cerr<<ans1<<' '<<ans2<<endl;
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
