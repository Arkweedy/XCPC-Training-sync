#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

using Z = ll;

constexpr int N = 1.8e5 + 10;
vector<int>prime;
bitset<N + 1>isprime;

void seive()
{
    isprime.set();
    isprime[1] = 0;
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
}

auto min_25(ll n)
{
    constexpr int mod = 4;
    int m = floorl(sqrtl(n));
    // f(p^k) = p^k(p^k - 1) 
    // g(p) = p,  h(p) = p^2

    vector<array<ll,4>>g0(m + 1,array<ll,4>{}),g1(m + 1,array<ll,4>{});
    //g[i][j] -> g(2 ~ i) idxs mod eq j

    for(int i = 1;i <= m;i++){
        ll x = n / i; // long long !!!
        for(int j = 0;j < mod;j++){
            g0[i][j] = (i + mod - j) / mod - (j % mod <= 1);
            g1[i][j] = (x + mod - j) / mod - (j % mod <= 1);
        }
    }

    

    //G(n, k) = G(n, k - 1) - g(p_k)(G(n / p_k, k - 1) - G(p_k - 1, k - 1))
    //lpf = p_k, others is G(n / p_k, k - 1)

    for(auto p : prime){
        //每一步剔除的都是lpf = p 的数 y = p * x
        //转移的形式即为g(p) * (G(x) - G(p - 1)),G(x)代表原来的位置,
        //实际上排除的数为 y = p * x, 模也做对应的转移即可
        ll pp = 1ll * p * p;
        Z gp = 1;
        
        if(pp > n)break;

       
        //update 1
        for(int j = 1;j <= m && j * pp <= n;j++){
            // g1[j] += gp * g0[p - 1];
            // if(1ll * p * j <= m){
            //     g1[j] -= gp * g1[p * j];
                
            // }
            // else{
            //     g1[j] -= gp * g0[n / p / j];
                
            // } 
            

            for(int k = 0;k < mod;k++){
                g1[j][k * p % mod] += g0[p - 1][k];
                if(1ll * p * j <= m){
                    g1[j][k * p % mod] -= g1[p * j][k];
                }
                else{
                    g1[j][k * p % mod] -= g0[n / p / j][k];
                } 
            }
        }

     

        //update 0
        for(int j = m;j >= pp;j--){
            for(int k = 0;k < mod;k++){
                g0[j][k * p % mod] -= (g0[j / p][k] - g0[p - 1][k]);
            }
        }
    }

    auto ans = g1[1];

    return ans;
}

void solve()
{
    ll n;
    cin>>n;
    auto ans = min_25(n);
    cout<<ans[1]<<endl;
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