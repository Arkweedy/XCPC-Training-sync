#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int P = 998244353;
int _power(int a, int b) {
    int res = 1;
    for (; b; b /= 2, a = 1LL * a * a % P) {
        if (b % 2) {
            res = 1LL * res * a % P;
        }
    }
    return res;
}
vector<int> rev, roots{ 0, 1 };
void dft(vector<int>& a) {
    int n = a.size();
    if (int(rev.size()) != n) {
        int k = __builtin_ctz(n) - 1;
        rev.resize(n);
        for (int i = 0; i < n; i++) {
            rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
        }
    }
    for (int i = 0; i < n; i++) {
        if (rev[i] < i) {
            swap(a[i], a[rev[i]]);
        }
    }
    if (roots.size() < n) {
        int k = __builtin_ctz(roots.size());
        roots.resize(n);
        while ((1 << k) < n) {
            int e = _power(31, 1 << (__builtin_ctz(P - 1) - k - 1));
            for (int i = 1 << (k - 1); i < (1 << k); i++) {
                roots[2 * i] = roots[i];
                roots[2 * i + 1] = 1LL * roots[i] * e % P;
            }
            k++;
        }
    }
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                int u = a[i + j];
                int v = 1LL * a[i + j + k] * roots[k + j] % P;
                a[i + j] = (u + v) % P;
                a[i + j + k] = (u - v) % P;
            }
        }
    }
}
void idft(vector<int>& a) {
    int n = a.size();
    reverse(a.begin() + 1, a.end());
    dft(a);
    int inv = (1 - P) / n;
    for (int i = 0; i < n; i++) {
        a[i] = 1LL * a[i] * inv % P;
    }
}
vector<int> mul(vector<int> a, vector<int> b) {
    int n = 1, tot = a.size() + b.size() - 1;
    while (n < tot) {
        n *= 2;
    }
    if (tot < 128) {
        vector<int> c(a.size() + b.size() - 1);
        for (int i = 0; i < a.size(); i++) {
            for (int j = 0; j < b.size(); j++) {
                c[i + j] = (c[i + j] + 1LL * a[i] * b[j]) % P;
            }
        }
        return c;
    }
    a.resize(n);
    b.resize(n);
    dft(a);
    dft(b);
    for (int i = 0; i < n; i++) {
        a[i] = 1LL * a[i] * b[i] % P;
    }
    idft(a);
    for (int i = 0; i < n; i++) {
        a[i] = (a[i] + P) % P;
    }
    a.resize(tot);
    return a;
}

int inv(int a)
{
    return _power(a, P - 2);
}

template<typename T>
class bit //1 base
{
    int n;
    int upper;
    vector<T>tree;

    inline static const int lowbit(const int x)
    {
        return x & -x;
    }

public:
    bit(vector<T>& a)
    {
        n = a.size() - 1;
        tree = a;
        for (int i = 1; i <= n; i++) {
            if (i + lowbit(i) <= n) {
                tree[i + lowbit(i)] += tree[i];
            }
        }
        upper = n;
        if (lowbit(upper) != upper) {
            while (upper != lowbit(upper)) {
                upper -= lowbit(upper);
            }
            upper <<= 1;
        }
    }

    void add(int p, T x)
    {
        while (p <= n) {
            tree[p] += x;
            p += lowbit(p);
        }
    }

    T qry(int r)
    {
        T res = 0;
        while (r != 0) {
            res += tree[r];
            r -= lowbit(r);
        }
        return res;
    }

    T qry(int l, int r)
    {
        if (l > 0)
            return qry(r) - qry(l - 1);
        else
            return qry(r);
    }

    int findleq(T v)const //前缀和小于等于的最大位置
    {
        int p = 0;
        T sum = 0;
        for (int len = upper; len != 0; len >>= 1) {
            if (len + p <= n && sum + tree[len + p] <= v) {
                p += len;
                sum += tree[p];
            }
        }
        return p;
    }

    int findl(T v)const //严格小的最大位置
    {
        int r = upper;
        int p = 0;
        T sum = 0;
        for (int len = upper; len != 0; len >>= 1) {
            if (len + p <= n && sum + tree[len + p] < v) {
                p += len;
                sum += tree[p];
            }
        }
        return p;
    }
};


void solve()
{
    int n;
    cin>>n;
    vector<int>arr(n);
    for(int i = 0;i < n;i++){
        cin>>arr[i];
    }
    vector<int>tmp(n + 1);
    bit<int>t(tmp);
    vector<int>lens;
    int l = 0;
    for(int i = 0;i < n;i++){
        t.add(arr[i],1);
        if(t.qry(i + 1) == i + 1){
            lens.push_back(i - l + 1);
            l = i + 1;
        }
    }
    lens.push_back(n - l);

    vector<int>fac(n + 1);
    vector<int>k(n + 1);
    k[0] = 0;
    k[1] = 1;
    fac[0] = fac[1] = 1;
    for(int i = 2;i <= n;i++){
        k[i] = 1ll * k[i - 1] * i % P;
        fac[i] = 1ll * fac[i - 1] * i % P;
    }
    auto cdq1 = [&](auto&&self, int l, int r)->void
    {
        if(l == r)return;
        int m = l + r >> 1;
        self(self, l, m);
        //[l , m] * [1, r - l]
        vector<int>a(m - l + 1), b(r - l + 1);
        for(int i = 0; i <= m - l;i++){
            a[i] = k[i + l];
        }
        for(int i = 0;i <= r - l;i++){
            b[i] = fac[i + 1];
        }
        auto c = mul(a, b);//[l + 1, r - m + l]
        for(int i = m + 1;i <= r;i++){
            k[i] = (1ll*k[i] - c[i - 1 - l] + P) % P;
        }
        self(self, m + 1, r);
    };
    cdq1(cdq1,1,n);
    vector<int>f(n + 1);
    vector<int>invfac(n + 1);
    for(int i = 1;i <= n;i++){
        invfac[i] = inv(fac[i]);
        k[i] = 1ll * k[i] % P;
    }
    vector<int>p(n + 1);
    for(int i = 1; i<= n;i++){
        p[i] = (1 - (1ll * k[i] * invfac[i] % P) + P) % P;
    }
    f[0] = f[1] = -1;
    auto cdq2 = [&](auto&&self, int l ,int r)->void
    {
        if(l == r){
            //cerr<<"f["<<l<<"]:"<<endl;cerr<<f[l]<<" ";
            if(l == 1)return;
            f[l] = (f[l] + k[l]) % P;
            f[l] = 1ll * f[l] * invfac[l] % P;
            f[l] = 1ll * f[l] * inv(p[l]) % P;
            return;
        }
        int m = l + r >> 1;
        self(self, l, m);
        {
            vector<int>a(m - l + 1), b(r - l + 1);
            for(int i = 0;i <= m - l;i++){
                a[i] = 1ll * k[i + l] * (f[i + l] + 1) % P;
            }
            for(int i = 0;i <= r - l;i++){
                b[i] = fac[i + 1];
            }
            auto c = mul(a, b);//[l + 1, r - m + l]
            for(int i = m + 1;i <= r;i++){
                f[i] = (1ll * f[i] + c[i - 1 - l]) % P;
            }
        }
        {
            vector<int>a(m - l + 1), b(r - l + 1);
            for(int i = 0;i <= m - l;i++){
                a[i] = 1ll * max(0,f[i + l]) * fac[i + l] % P;
            }
            for(int i = 0;i <= r - l;i++){
                b[i] = k[i + 1];
            }
            auto c = mul(a, b);//[l + 1, r - m + l]
            for(int i = m + 1;i <= r;i++){
                f[i] = (1ll * f[i] + c[i - 1 - l]) % P;
            }
        }
        self(self,m+1,r);
        return;
    };
    cdq2(cdq2,1,n);

    ll ans = 0;
    for(auto len : lens){
        ans += f[len] + 1;
    }
    ans %= P;
    cout<<ans<<endl;
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