#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int N = 20000001;
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
    ll n;
    cin>>n;
    auto calc = [&](ll x)->ll
    {
        ll res = 0;
        for(ll i = 2;i * i <= x;i++){
            res -= x / (i * i) * mu[i];
        }
        return x - res;
    };

    ll l = 0, r = n * 5;
    while(r - l > 1){
        ll m = l + r >> 1;
        ll res = calc(m);
        if(res < n){
            l = m;
        }
        else{
            r = m;
        }
    }
    cout<<r<<endl;
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