#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int N = 1000500;
vector<int>prime;
bitset<N + 1>isprime;
vector<int>mu;
vector<int>ok;

void seive()
{
    isprime.set();
    isprime[0] = isprime[1] = 0;
    ok.resize(N + 1);
    for (int i = 2; i <= N; i++) {
        if (isprime[i]){ 
            prime.push_back(i);
            ok[i] = 1;
        }
        
        for (auto &p : prime) {//p = lpf[i * p]
            if (p * i > N)break;
            isprime.flip(i * p);
            if (i % p == 0)break;
        }
    }
}


void solve()
{
    
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