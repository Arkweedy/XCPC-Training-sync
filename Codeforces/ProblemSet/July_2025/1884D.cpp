#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int N = 1e6+10;
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

void solve()
{
    int n;
    cin>>n;
    vector<int>c(n + 1);
    for(int i = 0;i < n;i++){
        int x;
        cin>>x;
        c[x]++;
    }
    vector<int>f(n + 1);
    for(int i = 1;i <= n;i++){
        for(int j = 1;j * i <= n;j++){
            f[i] += c[i * j];
        }
    }
    vector<ll>g(n + 1);
    for(int i = 1;i <= n;i++){
        for(int j = 1;j * i <= n;j++){
            g[i] += 1ll * f[i * j] * f[i * j] * mu[j];
        }
    }
    for(int i = 1;i <= n;i++){
        g[i] -= c[i];
        g[i] /= 2;
    }
    vector<int>nu(n + 1);
    for(int i = 1;i <= n;i++){
        nu[i] = c[i] == 0 ? 0 : 1;
    }

    for(int i = 1;i <= n;i++){
        for(int j = 1;i * j <= n;j++){
            nu[i * j] |= nu[i];
        }
    }

    ll ans = 1ll*n*(n - 1)/2;
    for(int i = 1;i <= n;i++){
        ans -= g[i] * nu[i];
    }
    cout<<ans<<endl;
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