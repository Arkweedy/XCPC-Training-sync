#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int N = 201;
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

ll power(ll a, ll p)
{
    ll res = 1;
    while(p != 0){
        if(p & 1){
            res = res * a;
        }
        a = a * a;
        p >>= 1;
    }
    return res;
}

void solve()
{
    int n;
    cin>>n;
    auto calc = [&](int p, int R)->int
    {
        int l = 0, r = R + 1;
        while(r - l > 1){
            int m = l + r >> 1;
            if(power(m,p) > n){
                r = m;
            }
            else{
                l = m;
            }
        }
        return l;
    };

    int up = __lg(n) + 1;
    int ans = n;//1 
    int r = n;
    for(int i = 2;i <= up;i++){
        r = calc(i,r);
        ans += mu[i] * (r - 1);
    }
    cout<<ans<<endl;
    return;
}

int main()
{
    freopen("ispower.in","r",stdin);
    freopen("ispower.out","w",stdout);
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