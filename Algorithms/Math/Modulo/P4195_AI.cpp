#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//P4195_AI.cpp Create time : 2025.12.22 02:55

i64 exgcd(i64 a, i64 b, i64 &x, i64 &y){
    if(!b){ x=1; y=0; return a; }
    i64 x1,y1;
    i64 g = exgcd(b, a%b, x1, y1);
    x = y1;
    y = x1 - (a/b)*y1;
    return g;
}

i64 inv_mod(i64 a, i64 mod){
    i64 x,y;
    i64 g = exgcd(a, mod, x, y);
    // 只有 gcd==1 才能求逆
    x %= mod;
    if(x < 0) x += mod;
    return x;
}

int powmod(int a, int e, int mod){
    i64 r = 1 % mod;
    a %= mod;
    while(e){
        if(e&1) r = 1ll * r * a % mod;
        a = 1ll * a * a % mod;
        e >>= 1;
    }
    return r;
}

// BSGS: 要求 gcd(a, mod) == 1，返回最小非负解，不存在返回 -1
i64 bsgs(i64 a, i64 b, i64 mod){
    a %= mod; b %= mod;
    if(mod == 1) return 0;
    if(b == 1 % mod) return 0;

    i64 m = (i64)ceil(sqrt((long double)mod));
    unordered_map<int, int> mp;
    mp.reserve((size_t)m * 2);

    // 存 b * a^j
    i64 e = 1 % mod;
    for(i64 j=0;j<=m;j++){
        i64 val = (i64)((__int128)b * e % mod);
        mp[val] = j;              // 保留最大的 j，有利于得到更小的 x
        e = (i64)((__int128)e * a % mod);
    }

    i64 factor = powmod(a, m, mod);
    i64 cur = 1 % mod;            // a^{i*m}
    for(i64 i=1;i<=m+1;i++){
        cur = (i64)((__int128)cur * factor % mod);
        auto it = mp.find(cur);
        if(it != mp.end()){
            return i*m - it->second;
        }
    }
    return -1;
}

// exBSGS: 允许 gcd(a, p) != 1，返回最小非负解，不存在返回 -1
i64 exbsgs(i64 a, i64 b, i64 p){
    a %= p; b %= p;
    if(p == 1) return 0;
    if(b == 1 % p) return 0;

    // 可选：处理 a==0 的边界
    if(a == 0){
        if(b == 0) return 1;      // 0^1 = 0
        return -1;                // 0^x 永远不会是非0（mod p）
    }

    i64 k = 0;
    i64 d = 1 % p;
    while(true){
        i64 g = std::gcd(a, p);
        if(g == 1) break;
        if(b % g != 0) return -1;

        p /= g;
        b /= g;
        d = d * (a / g) % p;
        k++;

        if(d == b) return k;      // 关键：中途命中 x=k
    }

    // 现在 gcd(a,p)=1
    i64 rhs = (i64)((__int128)b * inv_mod(d, p) % p);
    i64 x = bsgs(a, rhs, p);
    if(x == -1) return -1;
    return x + k;
}


void solve()
{
    while(1){
        int a, b, p;
        cin >> a >> p >> b;
        if(a == 0 && b ==0 && p == 0)break;
        i64 ans = exbsgs(a, b, p);
        if(ans == -1) cout << "No Solution\n";
        else cout << ans << "\n";
    }
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