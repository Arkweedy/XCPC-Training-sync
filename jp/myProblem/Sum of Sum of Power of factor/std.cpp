#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


constexpr int P = 1000000007;

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

constexpr int N = 1e7 + 1000;
bitset<N + 1>isprime;
vector<int>prime;
vector<int>ak;
vector<int>prefix_ak;

void seive(int k)
{
    
    isprime.set();
    isprime[0] = isprime[1] = false;
    ak.resize(N + 1);
    prefix_ak.resize(N + 1);
    ak[1] = 1;
    prefix_ak[1] = 1;
    for(int i = 2;i <= N;i++){
        if(isprime[i]){
            prime.push_back(i);
            ak[i] = power(i, k);
        }
        for(auto p : prime){
            if(i * p > N)break;
            ak[i * p] = 1ll * ak[i] * ak[p] % P;
            isprime[i * p].flip();
            if(i % p == 0)break;
        }
    }
    for(int i = 2;i <= N;i++){
        prefix_ak[i] = (prefix_ak[i - 1] + ak[i]) % P;
    }
    return;
}

void solve()
{
    int n,k;
    cin>>n>>k;
    seive(k);
    //可以 sqrt(n) 处理多次询问
    auto calc = [&](int n)->int
    {
        int ans = 0;
        for(int l = 1,r;l <= n;l = r + 1){
            r = n / (n / l);
            ans = (ans + 1ll * (prefix_ak[r] - prefix_ak[l - 1] + P) % P * (n / l) % P) % P;
        }
        return ans;
    };
    cout<<calc(n)<<endl;
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}