#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.05.02 16:26:28

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

void solve()
{
    int n, k;
    cin >> n >> k;
    map<int,int>mp;
    int eq = 0;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
        if(a[i] == k){
            eq = 1;
        }
        if(a[i] >= k)continue;
        mp[a[i]]++;
    }

    if(n == 1 && a[0] == k){
        cout << 0 << endl;
        return;
    }

    i64 ans = power(2, k);

    int la = -1;
    int flg = 0;
    for(auto [x, c] : mp){
        ans -= 1ll * power(2, x) * min(c, 1 << min(29, k - c - 1));
        if(la + 1 != x)flg = 1;
        la = x;
    }
    if(la != k - 1)flg = 1;
    //cerr << la << endl;
    if(flg)eq = 0;
    if(eq)ans++;

    ans = (ans % P + P) % P;
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