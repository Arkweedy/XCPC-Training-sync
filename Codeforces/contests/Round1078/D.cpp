#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//D.cpp Create time : 2026.02.08 17:46

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>>a(n, vector<int>(m));
    int cnt = 0;
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            cin >> a[i][j];
            cnt += a[i][j];
        }
    }

    int k = cnt / 2;
    int sum = 0;
    int x = 0, y = 0;
    for(int i = 0;i < n;i++){
        for(int j = m - 1;j >= 0;j--){
            sum += a[i][j];
            if(sum == k){
                x = i;
                y = j;
            }
        }
    }

    string ans;
    //cerr << x << " " << y << endl;
    ans += string(x, 'D');
    ans += string(y, 'R');
    ans += 'D';
    ans += string(m - y, 'R');
    ans += string(n - x - 1, 'D');
    i64 res = 1ll * k * (cnt - k);
    cout << res << endl;
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