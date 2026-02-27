#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//D.cpp Create time : 2026.02.26 23:29

// V

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }

    // find max and cdq
    int len = __lg(n) + 1;
    vector<vector<int>>p(len, vector<int>(n));
    for(int i = 0;i < n;i++){
        p[0][i] = i;
    }

    auto maxp = [&](int x, int y)->int
    {
        return a[x] > a[y] ? x : y;
    };

    for(int i = 1;i < len;i++){
        for(int j = 0;(j + (1 << i) - 1) < n;j++){
            p[i][j] = maxp(p[i - 1][j], p[i - 1][j + (1 << i - 1)]);
        }
    }

    auto rmq = [&](int l, int r)->int
    {
        int len = r - l + 1;
        int k = __lg(len);
        return maxp(p[k][l], p[k][r - (1 << k) + 1]);
    };

    auto cdq = [&](auto&&self, int l, int r)->int
    {
        if(l >= r)return 0;
        int p = rmq(l, r);
        int lc = self(self, l, p - 1), rc = self(self, p + 1, r);
        return min(lc + (r - p), rc + (p - l));
    };

    int ans = cdq(cdq, 0, n - 1);
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