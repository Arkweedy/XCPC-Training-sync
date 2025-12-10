#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 2e5 + 10,M = 1e7 + 10,INF = 1e9,mod = 998244353;

int n,q,a[N],rt[N];
int ln[M],rn[M],tot;
ll s[M],cnt[M],mul[M];

ll qmi(ll a,ll k){
    ll res = 1;
    while(k){
        if(k&1)res = res * a % mod;
        k >>= 1;
        a = a * a % mod;
    }
    return res;
}

void insert(int &u,int v,int l,int r,int x){
    u = ++tot;
    ln[u] = ln[v],rn[u] = rn[v];
    cnt[u] = cnt[v] + 1;
    s[u] = s[v] + x;
    mul[u] = mul[v] * x % mod;
    if(l==r)return;
    int mid = l+r>>1;
    if(x>mid)return insert(rn[u],rn[v],mid+1,r,x);
    else insert(ln[u],ln[v],l,mid,x);
}

ll query(int u,int v,int l,int r,ll k){
    if(l==r){
        if(l==1)return 1;
        ll c = cnt[u] - cnt[v];
        k = min(c*(l-1),k);
        ll x = k/(l-1);
        ll y = k%(l-1);
        ll res = 1;

        if(y){
            res = qmi(l,c-x-1) * (l-y) % mod;
        }else{
            res = qmi(l,c-x);
        }

        return res; 
    }
    
    int mid = l+r>>1;
    ll c = s[ln[u]] - cnt[ln[u]] - (s[ln[v]]-cnt[ln[v]]);
    if(c >= k)return query(ln[u],ln[v],l,mid,k) * mul[rn[u]] % mod * qmi(mul[rn[v]],mod-2)%mod;
    else return query(rn[u],rn[v],mid+1,r,k-c);
}

void solve()
{
    mul[0] = 1;
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        insert(rt[i],rt[i-1],1,INF,a[i]);
    }
    while(q--){
        int l,r;cin>>l>>r;
        ll k;cin>>k;
        cout<<query(rt[r],rt[l-1],1,INF,k)<<'\n';
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    while(tt--){
        solve();
    }
    return 0;
}