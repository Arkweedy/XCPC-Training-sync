#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

mt19937 g(chrono::steady_clock::now().time_since_epoch().count());

constexpr int P1 = 998244353;
constexpr int P2 = 1e9 + 7;

struct Hash
{
    vector<int>h1,h2;
    vector<int>bk1,bk2;
    static constexpr int b1 = 114514, b2 = 1919810;


    Hash(string &s)
    {
        int n = s.length();
        h1.resize(n);
        h2.resize(n);
        bk1.resize(n);
        bk2.resize(n);
        bk1[0] = bk2[0] = 1;
        for(int i = 1;i < n;i++){
            bk1[i] = 1ll * bk1[i - 1] * b1 % P1;
            bk2[i] = 1ll * bk2[i - 1] * b2 % P2;
        }

        h1[0] = h2[0] = s[0];
        for(int i = 1;i < n;i++){
            h1[i] = 1ll * h1[i - 1] * b1 % P1;
            h2[i] = 1ll * h2[i - 1] * b2 % P2;
            h1[i] += s[i];
            h2[i] += s[i];
        }
    }

    pair<int,int> get(int l, int r)
    {
        int res1 = h1[r],res2 = h2[r];
        if(l > 0){
            res1 = (res1 - 1ll * h1[l - 1] * bk1[r - l + 1] % P1 + P1) % P1;
            res2 = (res2 - 1ll * h2[l - 1] * bk2[r - l + 1] % P2 + P2) % P2;
        }
        return make_pair(res1,res2);
    }
};

template<typename T>
struct Fenwick
{
    int n;
    vector<T> a;

    Fenwick(int n_ = 0)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        a.assign(n,T{});
    }

    void add(int x, const T& v)
    {
        for(int i = x + 1; i <= n; i += i& -i){
            a[i - 1] = (a[i - 1] + v + P1) % P1;
        }
    }

    //[0, x)

    T sum(int x)
    {
        T ans{};
        for(int i = x;i > 0;i -= i & -i){
            ans = (ans + a[i - 1] + P1) % P1;
        }
        return ans;
    }

    T query(int l, int r)
    {
        return (sum(r) - sum(l) + P1) % P1;
    }
};

template<typename T>
struct Fenwick1
{
    int n;
    vector<T> a;

    Fenwick1(int n_ = 0)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        a.assign(n,T{});
    }

    void add(int x, const T& v)
    {
        for(int i = x + 1; i <= n; i += i& -i){
            a[i - 1] = a[i - 1] + v;
        }
    }

    //[0, x)

    T sum(int x)
    {
        T ans{};
        for(int i = x;i > 0;i -= i & -i){
            ans = ans + a[i - 1];
        }
        return ans;
    }

    T query(int l, int r)
    {
        return sum(r) - sum(l);
    }
};




void solve()
{
    string s, t;
    cin>>s>>t;
    //cerr<<b1<<" "<<b2<<endl;
    Hash hs(s),ht(t);
    int n = s.length(), m = t.length();
    auto lcp = [&](int p1, int p2)->int //return same length
    {
        int l = 0, r = min(n - p1, m - p2) + 1;
        while(r - l > 1){
            int m = l + r >> 1;
            auto res1 = hs.get(p1,p1 + m - 1), res2 = ht.get(p2,p2 + m - 1);
            if(res1 == res2){
                l = m;
            }
            else{
                r = m;
            }
        }
        return l;
    };

    

    vector<int>next(n);
    for(int i = 0;i < n;i++){
        int a = lcp(i, 0);
        if(i + a == n || a == m){
            next[i] = i + a - 1;
        }
        else{
            int b = lcp(i + a + 1, a + 1);
            next[i] = i + a + b;
        }
    }

    Fenwick<ll>f0(n + 1),f1(n + 1),f2(n + 1);//offset = 1
    f0.add(0, 1);
    f0.add(1, -1);
    for(int i = 0;i < n;i++){
        // \sum (n + 1) ^ 2 = 1 + \sum n ^ 2 + \sum 2 * n + \sum 1
        // \sum n + 1 = 
        // 1

        // val = i + 1;
        // [i, next[i]] is ok
        // dp[i - 1] -> dp[i ~ next[i]]
        int l = i + 1, r = next[i] + 1;
        ll x0 = f0.sum(i + 1);
        ll x1 = f1.sum(i + 1);
        ll x2 = f2.sum(i + 1);
        ll t0 = (x0) % P1;
        ll t1 = (x1 + x0) % P1;
        ll t2 = (x2 + 2 * x1 + x0) % P1;

        f0.add(l, t0);
        f0.add(r + 1, -t0);
        f1.add(l, t1);
        f1.add(r + 1, -t1);
        f2.add(l, t2);
        f2.add(r + 1, -t2);
    }

    cout<<f2.sum(n + 1) % P1<<endl;
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