#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int N = 3e5;
constexpr ll M = 4e10;


bitset<N + 1>isprime;
vector<int>prime;

void seive()
{
    isprime.set();
    isprime[1] = 0;
    prime.push_back(1); //0 = 1;
    for(int i = 2;i <= N;i++){
        if(isprime[i]){
            prime.push_back(i);
        }
        
        for(auto p : prime){
            if(p == 1)continue;
            if(i * p > N)break;
            isprime[i * p].flip();
            if(i % p == 0)break;
        }
    }
}

int P, k;

static inline i64 add(i64 a, i64 b) {
    a += b; if (a >= P) a -= P; return a;
}
static inline i64 sub(i64 a, i64 b) {
    a -= b; if (a < 0) a += P; return a;
}
static inline i64 mul(i64 a, i64 b) {
    return (a * b) % P;
}
static inline i64 power(i64 a, int e) {
    i64 r = 1;
    a %= P;
    while (e) {
        if (e & 1) r = mul(r, a);
        a = mul(a, a);
        e >>= 1;
    }
    return r;
}

// -------- 拉格朗日插值预处理 --------
// 我们需要快速计算 S(x) = sum_{i=1..x} i^k (P).
// 经典做法：用 m = k+2 个点做一次性插值，之后 O(k) 求任意整数点。
static int mpt;            // m = k + 2
static i64 pref_prod[20];  // 前缀积 (N-1)(N-2)...(N-i)
static i64 suff_prod[20];  // 后缀积 (N-(i+1))...(N-m)
static i64 inv_fac[20];    // 1/(i!) 的前缀（实际上是阶乘逆）
static i64 yval[20];       // y[i] = sum_{t=1..i} t^k

static void init_lagrange() {
    mpt = k + 2;

    // y[i] 前缀幂和：y[i] = sum_{t=1..i} t^k
    yval[0] = 0;
    for (int i = 1; i <= mpt; ++i)
        yval[i] = add(yval[i-1], power(i, k));

    // inv_fac[i]：i! 的逆元（线性递推 + 前缀积得到阶乘逆）
    inv_fac[0] = inv_fac[1] = 1;
    for (int i = 2; i <= mpt; ++i) {
        // 费马小定理下的线性递推 inv[i]，要求 P 为素数
        inv_fac[i] = mul(inv_fac[P % i], (P - P / i));
    }
    // 现在 inv_fac[i] 还是“单个 i 的逆”，把它累乘成 “i! 的逆”
    for (int i = 2; i <= mpt; ++i) {
        inv_fac[i] = mul(inv_fac[i], inv_fac[i - 1]);
    }

    // 前缀积与后缀积在求拉格朗日插值时复用
    pref_prod[0] = 1;
}

// 计算 S(N) = sum_{i=1..N} i^k (P)；N 可以很大。
// 使用 m = k+2 点的拉格朗日插值；点坐标是 1..m。
static inline i64 sum_pows(i64 X) {
    X %= P;

    // 构造 (X-1)(X-2)...(X-i)
    for (int i = 1; i <= mpt; ++i) {
        pref_prod[i] = mul(pref_prod[i - 1], (X - i + P) % P);
    }
    // 构造 (X-(i+1))...(X-m)
    suff_prod[mpt + 1] = 1;
    for (int i = mpt; i >= 1; --i) {
        suff_prod[i] = mul(suff_prod[i + 1], (X - i + P) % P);
    }

    // 经典拉格朗日（横坐标为 1..m），注意 (-1)^(m-i) 的号
    i64 ans = 0;
    for (int i = 1; i <= mpt; ++i) {
        // 基函数：prod_{j!=i} (X - j) / (i - j)
        i64 num = mul(pref_prod[i - 1], suff_prod[i + 1]);  // 分子
        // 分母 (i-1)! * (m-i)! 的逆，且要乘 (-1)^(m-i)
        i64 den = mul(inv_fac[i - 1], inv_fac[mpt - i]);
        if ((mpt - i) & 1) den = (P - den) % P; // (-1)^(m-i)

        // 贡献：y[i] * num * den
        ans = (ans + mul(mul(yval[i], num), den)) % P;
    }
    return ans;
}

void solve()
{
    ll n;
    cin>>n>>k>>P;

    init_lagrange();

    int limit = floorl(sqrtl(n));
    vector<int>h0(limit + 1),h1(limit + 1);

    //calc h0,h1 for limit rounds

    for(int i = 1;i <= limit;i++){
        h0[i] = sub(sum_pows(i) , 1);
        h1[i] = sub(sum_pows(n / i) , 1);
    }

    for(int i = 1;prime[i] <= limit;i++){
        int ppow = power(prime[i], k);
        ll pp = 1ll * prime[i] * prime[i];
        int pi = prime[i], pii = prime[i - 1];
        for(int j = 1;j <= limit && pp * j <= n;j++){
            h1[j] = add(h1[j], mul(ppow, h0[pii]));
            if(1ll * pi * j <= limit)
                h1[j] = sub(h1[j], mul(ppow, h1[pi * j]));
            else
                h1[j] = sub(h1[j], mul(ppow,h0[n / pi / j]));
        }

        for(int j = limit; pp <= j ;j--){
            h0[j] = sub(h0[j] , mul(ppow ,sub(h0[j / pi], h0[pii])));
        }
    }

    ll ans = 0;
    for(int i = 1;i <= limit;i++){
        ans = ans + mul(mul(h1[i],i),i);
        ans %= P;
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
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}