#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//1006.cpp Create time : 2026.05.16 01:27

constexpr int N = 1000000;
vector<int>prime;
bitset<N + 1>isprime;
vector<int>mu;

void seive()
{
    isprime.set();
    mu.resize(N + 1);
    isprime[0] = isprime[1] = 0;
    mu[1] = 1;
    for (int i = 2; i <= N; i++) {
        if (isprime[i]) {
            prime.push_back(i);
            mu[i] = -1;
        }
        for (auto &p : prime) {//p = lpf[i * p]
            if (p * i > N)
                break;
            isprime.flip(i * p);
            //mu
            if (i % p == 0) {
                mu[i * p] = 0;
                break;
            }
            else {
                mu[i * p] = mu[i] * (-1);
            }
        }
    }
}

constexpr int P = 1e9 + 7;

void solve()
{
    int n, m;
    cin >> n >> m;
    constexpr int N = 1e6;
    vector<int>ca(N + 1), cb(N + 1);
    for(int i = 0;i < n;i++){
        int e;
        cin >> e;
        ca[e]++;
    }
    for(int i = 0;i < m;i++){
        int e;
        cin >> e;
        cb[e]++;
    }

    auto dirichlet = [&](vector<int>&a)->void
    {
        for(auto p : prime){
            for(int i = N / p;i >= 1;i--){
                a[i] = (a[i] + 1ll * p * a[p * i]) % P;
            }
        }
    };

    auto getM = [&](vector<int>&a)->void
    {   
        for(int i = 1;i <= N;i++){
            a[i] = (1ll * a[i] * i * i % P + P) % P;
        }
        for(auto p : prime){
            for(int i = 1;i * p <= N;i++){
                a[i * p] = (a[i * p] + a[i]) % P;
            }
        }
    };

    getM(mu);
    dirichlet(ca);
    dirichlet(cb);

    int ans = 0;
    for(int i = 1;i <= N;i++){
        //cerr << ca[i] << " " << cb[i] << endl;
        ans = ((ans + 1ll * mu[i] * ca[i] % P * cb[i]) % P + P) % P;
    }
    cout << ans << endl;
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    seive();
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}