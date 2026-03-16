#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.03.16 16:10:38

constexpr int N = 10000;
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

i64 power(i64 a, i64 p)
{
    i64 res = 1;
    while(p){
        if(p & 1)res = res * a;
        a = a * a;
        p >>= 1;
    }
    return res;
}

void solve()
{
    constexpr i64 N = 2e18 + 1;
    cerr << N << endl;
    i64 a, b;
    cin >> a >> b;
    i64 n = 1, m = 1;
    reverse(prime.begin(),prime.end());
    for(auto p : prime){
        i64 g = gcd(a, b);
        a /= g;
        b /= g;
        //cerr << "calc " << p << " " << a << " " << b << endl;
        
        if(a % p == 0){
            int var = 0;
            while(a % p == 0){
                a /= p;
                var++;
            }
            if(var % 2 == 0){
                int k = var / 2 + 1;
                n *= power(p, k);
                m *= p;
            }
            else{
                int k = var / 2 + 1;
                n *= power(p, k);
                b *= (p - 1);
            }
        }
        else if(b % p == 0){
            int var = 0;
            while(b % p == 0){
                b /= p;
                var++;
            }
            if(var % 2 == 0){
                int k = var / 2 + 1;
                m *= power(p, k);
                n *= p;
            }
            else{
                int k = var / 2 + 1;
                m *= power(p, k);
                a *= (p - 1);
            }
        }
        //cerr << a << " " << b << " " << n << " " << m << endl;
    }
    reverse(prime.begin(),prime.end());
    cout << n << " " << m << endl;
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