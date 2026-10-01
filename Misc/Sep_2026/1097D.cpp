#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//1097D.cpp Create time : 2026.09.26 09:33
constexpr int P = 1e9 + 7;

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

struct Comb {
    int n;
    std::vector<int> _fac;
    std::vector<int> _invfac;
    std::vector<int> _inv;
     
    Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
    Comb(int n) : Comb() {
        init(n);
    }
     
    void init(int m) {
        if (m <= n) return;
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);
         
        for (int i = n + 1; i <= m; i++) {
            _fac[i] = 1ll * _fac[i - 1] * i % P;
        }
        _invfac[m] = power(_fac[m], P - 2);
        for (int i = m; i > n; i--) {
            _invfac[i - 1] = 1ll * _invfac[i] * i % P;
            _inv[i] = 1ll * _invfac[i] * _fac[i - 1] % P;
        }
        n = m;
    }
     
    int fac(int m) {
        if (m > n) init(2 * m);
        return _fac[m];
    }
    int invfac(int m) {
        if (m > n) init(2 * m);
        return _invfac[m];
    }
    int inv(int m) {
        if (m > n) init(2 * m);
        return _inv[m];
    }
    int binom(int n, int m) {
        if (n < m || m < 0) return 0;
        return 1ll * fac(n) * invfac(m) % P * invfac(n - m) % P;
    }
} comb;

void solve()
{
    i64 n;
    int k;
    cin >> n >> k;
    vector<pair<i64,int>>facs;
    for(i64 i = 2;i * i <= n;i++){
        if(n % i == 0){
            int c = 0;
            while(n % i == 0){
                n /= i;
                c++;
            }
            facs.emplace_back(i, c);
        }
    }
    if(n != 1)facs.emplace_back(n, 1);

    
    i64 ans = 1;
    for(auto [p, c] : facs){
        vector<int>pr(c + 1);
        pr[c] = 1;
        for(int i = 0;i < k;i++){
            int tr = 0;
            for(int j = c;j >= 0;j--){
                pr[j] = 1ll * pr[j] * comb.inv(j + 1) % P;
                tr = (tr + pr[j]) % P;
                pr[j] = tr;
            }
        }

        i64 res = 0;
        i64 x = 1;
        for(int i = 0;i <= c;i++){
            res = (res +  1ll * pr[i] * x) % P;
            if(i < c)x = 1ll * x * p % P;
        }
        ans = ans * res % P;
    }

    cout << ans << endl;
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