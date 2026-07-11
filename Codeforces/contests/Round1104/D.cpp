#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//D.cpp Create time : 2026.06.18 23:24

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int>a(n), b(n);
    for(int i = 0;i < n;i++){
        a[i] = s[i] - '0';
        if(a[i] == 1)b[i] = 1;
        else b[i] = 2;
        if(i % 2 == 1)a[i] ^= 1;

    }
    // no : all same except 1;
    //      b[l, r] mod 3 == 0
    i64 res = 0;
    vector<int>c(3);
    c[0] = 1;
    for(int i = 0;i < n;i++){
        if(i > 0)b[i] = (b[i] + b[i - 1]) % 3;
        res += c[b[i]];
        c[b[i]]++;
    }

    auto calc = [&](int x)->i64
    {
        i64 res = 1ll * (x + 1) * x / 2;
        res -= x; // len = 1, ok
        if(x <= 1)return res;
        int d = 2, r = x - 1, l = (x + 1) % 2;
        res -= 1ll * (r + l) * (r - l + d) / d / 2;
        return res;
    };

    int la = -1;
    int x = 0;
    for(int i = 0;i < n;i++){
        if(a[i] == la){
            x++;
        }
        else{
            res += calc(x);
            x = 1;
        }
        la = a[i];
    }
    res += calc(x);
    i64 ans = 1ll * n * (n + 1) / 2 - res;
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