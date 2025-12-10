#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int MAX_SIEVE = 3000000;
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
    ll l , r;
    cin>>l>>r;
    auto calc = [&](ll n)->ll
    {
        // 处理1 ~ M - 1的质数
        ll res = 0;
        // 
        for(int i = 1;1ll * p[i] * p[i] <= n + p[i] && p[i] < M;i++){
            res += floorl(sqrtl((n + p[i]) / (1ll * p[i] * p[i])));
        }
        
        //处理 M  ~ 约sqrt(n)的质数
        ll rt = floorl(sqrtl((n + M) / (1ll * M * M)));// 当前贡献
        auto find_r = [&](ll l)->ll
        {
            ll L = l, R = 2e9;
            while(R - L > 1){
                ll Md = L + R >> 1;
                if((n + Md) / (Md * Md) >= rt * rt){
                    L = Md;
                }
                else{
                    R = Md;
                }
            }
            return L;
        };
        for(ll l = M, r;l * l <= l + n;l = r + 1){
            //rt(l) == rt(r) == rt
            r = find_r(l);
            res += (get_pcnt(r) - get_pcnt(l - 1)) * rt;
            rt--;
        }
        return res;
    };

    ll ans = calc(r) - calc(l - 1);
    cout<<ans<<endl;
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    init_primes();
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}