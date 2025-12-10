#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.10.29 16:26:15

constexpr int N = 1e6;
vector<int>prime;
bitset<N + 1>isprime;
void seive()
{
    isprime.set();
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
    return;
}


constexpr int P = 998244353;
constexpr int Inv2 = 499122177;
constexpr int Inv6 = 166374059;

void norm(ll& x)
{
    x %= P;
    if(x < 0)x += P;
    return;
}

int power(int a, int p)
{
    int res = 1;
    while(p){
        if(p & 1)res = 1ll * res * a % P;
        a = 1ll * a * a % P;
        p >>= 1;
    }
    return res;
}

int inv(int a)
{
    return power(a, P - 2);
}

ll min_25(ll n)
{
    //calc \sum_n n*\sigma(n)
    // 
    ll m = sqrtl(n);
    vector<ll>g0(m + 1),g1(m + 1);
    vector<ll>h0(m + 1),h1(m + 1);
    for(ll i = 1;i <= m;i++){
        ll x = n / i % P;
        g0[i] = i * (i + 1) % P * Inv2 % P - 1;
        g1[i] = x * (x + 1) % P * Inv2 % P - 1;
        h0[i] = i * (i + 1) % P * (i * 2 + 1) % P * Inv6 % P - 1;
        h1[i] = x * (x + 1) % P * (x * 2 + 1) % P * Inv6 % P - 1;
        norm(g0[i]);
        norm(g1[i]);
        norm(h0[i]);
        norm(h1[i]);
    }

    for(auto p : prime){
        ll pp = 1ll * p * p;
        ll gp = p;
        ll hp = 1ll * p * p % P;
        if(pp > n)break;
        //update 1
        for(int j = 1;j <= m && j * pp <= n;j++){
            g1[j] += gp * g0[p - 1];
            h1[j] += hp * h0[p - 1];
            norm(g1[j]);
            norm(h1[j]);
            if(1ll * p * j <= m){
                g1[j] -= gp * g1[p * j];
                h1[j] -= hp * h1[p * j];
                norm(g1[j]);
                norm(h1[j]);
            }
            else{
                g1[j] -= gp * g0[n / p / j];
                h1[j] -= hp * h0[n / p / j];
                norm(g1[j]);
                norm(h1[j]);
            } 
        }

        //update 0
        for(int j = m;j >= pp;j--){
            g0[j] -= gp * (g0[j / p] - g0[p - 1]);
            h0[j] -= hp * (h0[j / p] - h0[p - 1]);
            norm(g0[j]);
            norm(h0[j]);
        }
    }

    // vector<ll>fprime0(m + 1),fprime1(m + 1);
    // for(int i = 1;i <= m;i++){
    //     fprime0[i] = (g0[i] + h0[i]) % P;
    //     fprime1[i] = (g1[i] + h1[i]) % P;
    // }

    //cerr<<g1[1]<<" "<<g1[2]<<" "<<h1[1]<<" "<<h1[2]<<endl; 

    ll x = n % P;
    ll res = (1 + x) * x % P * Inv2 % P;
    //2 + 3 + 4 + ... + n except prime in [n / 2 + 1, n]
    res -= g1[1] - g1[2];
    res -= 1;
    norm(res);
    res = res * res % P;
    res -= x * (x + 1) % P * (x * 2 + 1) % P * Inv6 % P;
    res += 1;
    res += h1[1] - h1[2];
    res *= Inv2;
    norm(res);
    return res;
}



void solve()
{
    ll n;
    cin>>n;
    ll ans = min_25(n);
    cout<<ans<<endl;
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    seive();
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}