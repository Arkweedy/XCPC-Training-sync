#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.03.17 00:54:29

constexpr int P = 998244353;

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

int inv(int a)
{
    return power(a, P - 2);
}

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int>a(n), b(m);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    for(int i = 0; i < m; i++){
        cin >> b[i];
    }

    vector<int>sa = a;
    sort(sa.begin(),sa.end());
    sa.erase(unique(sa.begin(), sa.end()), sa.end());
    int len = sa.size();
    for(int i = 0;i < n;i++){
        a[i] = lower_bound(sa.begin(),sa.end(), a[i]) - sa.begin();
    }


    vector<int> lc(n, -1), rc(n, -1), fa(n, -1), stk;
    stk.reserve(n);
    for (int i = 0; i < n; i++) {
        int last = -1;
        while (!stk.empty() && a[stk.back()] >= a[i]) {
            last = stk.back();
            stk.pop_back();
        }
        if (last != -1) {
            lc[i] = last;
            fa[last] = i;
        }
        if (!stk.empty()) {
            rc[stk.back()] = i;
            fa[i] = stk.back();
        }
        stk.push_back(i);
    }
    int root = stk.front();
    vector<i64>f(len);
    auto dfs = [&](auto&&self, int p, int l, int r)->void
    {
        f[a[p]] += 1ll * (p - l + 1) * (r - p + 1);
        f[a[p]] %= P;
        if(lc[p] != -1)self(self, lc[p], l, p - 1);
        if(rc[p] != -1)self(self, rc[p], p + 1, r);
        return;
    };
    dfs(dfs, root, 0, n - 1);
    
    int base = 0;
    for(int i = 0;i < n;i++){
        base = (base + 1ll * (n - i) * (i + 1) % P * inv(sa[a[i]])) % P;
    }
    vector<int>pf(n), pg(n), ph(n);
    for(int i = 0;i < len;i++){
        pf[i] = f[i];
        pg[i] = sa[i] * f[i] % P;;
        ph[i] = inv(sa[i]) * f[i] % P;

        if(i > 0){
            pf[i] = (pf[i] + pf[i - 1]) % P;
            pg[i] = (pg[i] + pg[i - 1]) % P;
            ph[i] = (ph[i] + ph[i - 1]) % P;
        }
    }

    auto getl = [&](int p, int k)->i64
    {
        if(p == 0)return 0;
        i64 res = 1ll * (k + 2) * pf[p - 1] - pg[p - 1] - ph[p - 1];
        res = (res % P + P) % P;
        return res;
    };

    auto getr = [&](int p, int k)->i64
    {
        if(p == len)return 0;
        i64 res = ph[len - 1];
        if(p > 0)res = (res - ph[p - 1] + P) % P;
        res = res * k % P;
        return res;
    };

    // p -> first ge
    int p = 0;
    vector<int>ans(m);
    for(int i = 0;i < m;i++){
        int k = b[i];
        while(p < len && k >= sa[p])p++;
        ans[i] = (base + getl(p, k) + getr(p, k)) % P;
    }

    for(int i = 0;i < m;i++){
        cout << ans[i] << "\n";
    }
    cout << endl;
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