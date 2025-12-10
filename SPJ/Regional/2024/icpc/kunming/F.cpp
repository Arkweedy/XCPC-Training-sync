#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

int P = 998244353;
constexpr int N = 2e5;
bitset<N + 1>isprime;
vector<int>prime;

void sieve()
{
    isprime.set();
    isprime[0] = isprime[1] = 0;
    for(int i = 2;i <= N;i++){
        if(isprime[i]){
            prime.push_back(i);
        }
        for(auto p : prime){
            if(i * p > N)break;
            isprime[i * p].flip();
            if(i % p == 0)break;
        }
    }
}

vector<ll>g0,g1;
ll m;
void min_25(ll n)
{
    m = floorl(sqrtl(n));
    g0.resize(m + 1);
    g1.resize(m + 1);
    
    for(int i = 1;i <= m;i++){
        ll x = n / i;
        g0[i] = i - 1;
        g1[i] = x - 1;
    }

    for(auto p : prime){
        ll pp = 1ll * p * p;
        if(pp > n)break;
        for(int j = 1;j <= m && j * pp <= n;j++){
            g1[j] += g0[p - 1];
            if(1ll * j * p <= m)g1[j] -= g1[j * p];
            else g1[j] -= g0[n / j / p];
        }
        for(int j = m;j >= pp; j--){
            g0[j] -= (g0[j / p] - g0[p - 1]);
        }
    }
    return;
}



ll power(ll a, ll p)
{
    ll res = 1;
    while(p){
        if(p & 1)res = res * a % P;
        a = a * a % P;
        p >>= 1;
    }
    return res;
}

void solve()
{
    ll n;
    cin>>n>>P;
    min_25(n);
    auto pi = [&](ll x)->ll
    {
        if(x <= m)return g0[x];
        else return g1[n / x];
    };
    
    auto get = [&](auto&self, ll n, int k, int c)->ll //
    {
        if(c == 1){
            ll res = pi(n) - k;
            for(int i = k;1ll * prime[i] * prime[i] <= n;i++){
                ll pj = 1ll * prime[i] * prime[i];//!!! 1ll * 
                for(int j = 2;pj <= n;pj *= prime[i]){
                    res++;
                }
            }
            return res;
            //return pi(n) - k;
        }
        ll res = 0;
        for(int i = k;1ll * prime[i] * prime[i] <= n;i++){
            ll pj = prime[i];
            for(int j = 1;pj * prime[i] <= n;j++,pj *= prime[i]){
                res += self(self,n / pj, i + 1, c - 1);
            }
        }
       
        return res;
    };

    ll ans = 1;
    for(int i = 2;i <= 10;i++){
        //cerr<<get(get,n,0,i) % (P - 1)<<endl;
        ans = ans * power(i, get(get,n,0,i) % (P - 1)) % P;
    }
    cout<<ans<<endl;
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    sieve();
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}