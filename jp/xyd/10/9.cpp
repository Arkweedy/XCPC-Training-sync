#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int N = 40000100;
vector<int>prime;
vector<ll>pp;
bitset<N + 1>isprime;


void seive()
{
    isprime.set();
    isprime[0] = isprime[1] = 0;
    for (int i = 2; i <= N; i++) {
        if (isprime[i]) 
            prime.push_back(i);
        
        for (auto &p : prime) {//p = lpf[i * p]
            if (p * i > N)break;
            isprime.flip(i * p);
            if (i % p == 0)break;
        }
    }
    pp.resize(prime.size() + 1);
    for(int i = 1;i < pp.size();i++){
        pp[i] = pp[i - 1] + prime[i - 1];
    }
}

void solve()
{
    
    int n;
    cin>>n;
    int up = lower_bound(pp.begin(),pp.end(),n) - pp.begin();
    int ans = 0;
    for(int i = 1;i <= up;i++){
        int p = lower_bound(prime.begin(),prime.end(),n / i) - prime.begin() + 1;
        while(p >= 0 && pp[p + i] - pp[p] >= n){
            if(pp[p + i] -pp[p] == n){
                ans++;
                break;
            }
            p--;
        }
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