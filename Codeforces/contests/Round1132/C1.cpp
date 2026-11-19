#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//C.cpp Create time : 2026.11.06 23:03

constexpr int N = 200000;
vector<int>prime;
bitset<N + 1>isprime;
vector<int>mu;

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
}


void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    auto get = [&](int x)->int
    {
        if(x == 1)return x;
        if(isprime[x])return x;
        int p = lower_bound(prime.begin(),prime.end(), x) - prime.begin();
        while(gcd(prime[p] - x, x) != 1)p++;
        return prime[p];
    };
    for(int i = 0;i < n;i++){
        a[i] = get(a[i]);
    }
    for(int i = 0;i < n;i++){
        cout << a[i] << " ";
    }
    cout << endl;
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