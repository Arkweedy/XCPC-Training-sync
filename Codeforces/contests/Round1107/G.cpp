#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//G.cpp Create time : 2026.07.04 17:51

ostream &operator<<(ostream &os, i128 n) {
    if (n == 0) {
        return os << 0;
    }
    string s;
    while (n > 0) {
        s += char('0' + n % 10);
        n /= 10;
    }
    reverse(s.begin(), s.end());
    return os << s;
}

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    int len = __lg(n) + 1;
    vector<vector<int>>st(len, vector<int>(n));
    for(int i = 0;i < n;i++){
        st[0][i] = a[i];
    }
    for(int i = 1;i < len;i++){
        for(int j = 0;j + (1 << i) - 1 < n;j++){
            st[i][j] = std::gcd(st[i - 1][j], st[i - 1][j + (1 << i - 1)]);
        }
    }

    auto get = [&](int l, int r)->int
    {
        int le = r - l + 1;
        int k = __lg(le);
        return std::gcd(st[k][l], st[k][r - (1 << k) + 1]);
    };

    auto next = [&](int l, int p)->int
    {
        int g = get(l, p);
        p++;
        for(int i = len - 1;i >= 0;i--){
            if(p + (1 << i) - 1 >= n)continue;
            if(st[i][p] % g == 0)p += 1 << i;
        }
        return p;
    };
    i128 ans = 0;
    for(int i = 0;i < n;i++){
        int p = i;
        int g = a[i];
        int d = 0;
        while(p != n){
            int np = next(i, p);
            int le = np - p;
            g = get(i, np - 1);
            ans += 1ll * le * d;
            if(np != n)d = max(d, min(a[np] % g, g - a[np] % g));
            p = np;
        }
    }
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