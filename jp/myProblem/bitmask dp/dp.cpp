#include<bits/stdc++.h>

#define ll long long
#define ull unsigned long long
using i64 = long long;

using namespace std;

int lowbit(int x)
{
    return (x & -x);
}

int count(int x)
{
    int res = 0;
    while (x != 0) {
        x -= lowbit(x);
        res++;
    }
    return res;
}


void solve()
{
    int n, m;
    cin >> n >> m;
    map<pair<int,int>, ll>dp;
    //dp[make_pair(0,0)] = 0;
    const int inf = (1 << m) - 1;
    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        int statu = 0;
        for (int i = 0; i < m; i++) {
            statu <<= 1;
            statu += (s[i] == 'H' ? 1 : 0);
        }
        map<pair<int, int>,ll>ndp;
        for (int a = 0; a <= inf; a++) {
            if ((a & (a << 1)) != 0 || (a & (a << 2)) != 0 || (a & statu) != 0) {
                continue;
            }
            for (int b = 0; b <= inf; b++) {
                if ((b & (b << 1)) != 0 || (b & (b << 2)) != 0 || (a&b) != 0) {
                    continue;
                }
                for (int c = 0; c <= inf; c++) {
                    if ((c & (c << 1)) != 0 || (c & (c << 2)) != 0 || (a&c) != 0 ||(b&c) != 0) {
                        continue;
                    }
                    else {
                        ndp[make_pair(a, b)] = max(ndp[make_pair(a, b)],dp[make_pair(b, c)] + count(a));
                    }
                }
            }
        }
        dp = move(ndp);
    }
    ll ans = 0;
    for (auto [pr, v] : dp) {
        ans = max(ans ,v);
    }
    cout << ans << endl;
    return;

}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    
        solve();
    return 0;
}