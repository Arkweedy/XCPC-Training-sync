#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int MAX_SIEVE = 300000;
constexpr int M = 2000000;

int p[MAX_SIEVE + 5], vis[MAX_SIEVE + 5], cnt;
ll vg[M], fg[M];
int idg1[M], idg2[M];


void init_primes() 
{
    cnt = 0;
    for (int i = 2; i <= MAX_SIEVE; i++) {
        if (!vis[i]) p[++cnt] = i;
        for (int j = 1; j <= cnt && i * p[j] <= MAX_SIEVE; j++) {
            vis[i * p[j]] = 1;
            if (i % p[j] == 0) break;
        }
    }
}


ll get_pcnt(ll n) {
    if (n <= 1) return 0;
    ll sqrt_n = sqrt(n);
    int m = 0;
 
    for (ll l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        vg[++m] = n / l;
        if (n / l <= sqrt_n) 
            idg1[n / l] = m;
        else 
            idg2[n / (n / l)] = m;
    }
  
    for (int i = 1; i <= m; i++) {
        fg[i] = vg[i] - 1;
    }
    
    for (int j = 1; j <= cnt && (ll)p[j] <= sqrt_n; j++) {
        for (int i = 1; i <= m && (ll)p[j] * p[j] <= vg[i]; i++) {
            ll t = vg[i] / p[j];
            int k;
            if (t <= sqrt_n) 
                k = idg1[t];
            else 
                k = idg2[n / t];
            fg[i] -= (fg[k] - (j - 1));
        }
    }
    return fg[1];
}


void solve()
{
    int l, r;
    cin>>l>>r;
    cout<<get_pcnt(r) - get_pcnt(l - 1)<<endl;
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    init_primes();
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}