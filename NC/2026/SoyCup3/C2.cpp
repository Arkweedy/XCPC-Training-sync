#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;
using i128 = __int128_t;

using namespace std;

//Create time: 2026.08.03 11:27:22
constexpr int P = 998244353;

i64 mul(i64 a, i64 b, i64 m) {
    return static_cast<__int128>(a) * b % m;
}
i64 power(i64 a, i64 b, i64 m) {
    i64 res = 1 % m;
    for (; b; b >>= 1, a = mul(a, a, m))
        if (b & 1)
            res = mul(res, a, m);
    return res;
}
bool isprime(i64 n) {
    if (n < 2)
        return false;
    static constexpr int A[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
    int s = __builtin_ctzll(n - 1);
    i64 d = (n - 1) >> s;
    for (auto a : A) {
        if (a == n)
            return true;
        i64 x = power(a, d, n);
        if (x == 1 || x == n - 1)
            continue;
        bool ok = false;
        for (int i = 0; i < s - 1; ++i) {
            x = mul(x, x, n);
            if (x == n - 1) {
                ok = true;
                break;
            }
        }
        if (!ok)
            return false;
    }
    return true;
}
vector<i64> factorize(i64 n) {
    vector<i64> p;
    function<void(i64)> f = [&](i64 n) {
        if (n <= 10000) {
            for (int i = 2; i * i <= n; ++i)
                for (; n % i == 0; n /= i)
                    p.push_back(i);
            if (n > 1)
                p.push_back(n);
            return;
        }
        if (isprime(n)) {
            p.push_back(n);
            return;
        }
        auto g = [&](i64 x) {
            return (mul(x, x, n) + 1) % n;
        };
        i64 x0 = 2;
        while (true) {
            i64 x = x0;
            i64 y = x0;
            i64 d = 1;
            i64 power = 1, lam = 0;
            i64 v = 1;
            while (d == 1) {
                                y = g(y);
                ++lam;
                v = mul(v, abs(x - y), n);
                if (lam % 127 == 0) {
                    d = gcd(v, n);
                    v = 1;
                }
                if (power == lam) {
                    x = y;
                    power *= 2;
                    lam = 0;
                    d = gcd(v, n);
                    v = 1;
                }
            }
            if (d != n) {
                f(d);
                f(n / d);
                return;
            }
            ++x0;
        }
    };
    f(n);
    sort(p.begin(), p.end());
    return p;
}

void solve()
{
    i64 n, p;
    cin >> n >> p;
    // \sum_{i = 1}^n (i - gcd(P + 1, i)) / 2 
    i64 m = n % P;
    i64 ans = m * (m + 1) / 2 % P;
    // calc gcd(p + 1, i)

    // f_N(i) = gcd(N, i) -> f(ab) = f(a)f(b) , gcd(a,b) = 1
    // decompose P + 1
    // Id = \phi * I
    // enum \prod_{p_i}^{k_i} , ans += n / \prod_{p_i}^{k_i} * \prod_ \phi({p_i}^{k_i})

    // 2 * 3 * 5 * 7 * 11 * 13 * 17 * 19 * 23 * 29 * 31 * 37 * 41 * 43 * 47 * 53 > 1e18 （15）

    i64 M = p + 1;
    auto factors = factorize(M);
    map<i64, int>mp;
    for(auto x : factors){
        mp[x]++;
    }
    vector<pair<i64,int>>fact;
    for(auto x : mp){
        fact.push_back(x);
    }

    i64 res = 0;
    int sz = fact.size();
    auto dfs = [&](auto&&self, int p, i64 prod, i64 phiprod)->void
    {
        if(p == sz){
            //cerr << prod << " " << phiprod << endl;
            res = (res + (n / prod) % P * (phiprod % P) % P) % P;
            return;
        }
        auto [x, c] = fact[p];
        for(int i = 0;i <= c && prod <= n;i++){
            self(self, p + 1, prod, phiprod);
            if(i == c)break;
            if(i == 0)phiprod *= (x - 1);
            else phiprod *= x;
            prod *= x;
        }
        return;
    };

    dfs(dfs, 0, 1, 1);
    ans = (ans - res + P) % P;
    ans = ans * power(2, P - 2, P) % P;
    cout << ans << endl;
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}