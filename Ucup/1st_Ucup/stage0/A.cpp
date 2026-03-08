#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//A.cpp Create time : 2026.03.04 08:52

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    string s;
    cin >> s;
    int x = 0, y = 0;
    int l = 0, r = 0, u = 0, d = 0;
    
    for(int i = 0;i < s.length();i++){
        if(s[i] == 'L'){
            x--;
            l = min(l, x);
        }
        else if(s[i] == 'R'){
            x++;
            r = max(r, x);
        }
        else if(s[i] == 'U'){
            y--;
            u = min(u, y);
        }
        else if(s[i] == 'D'){
            y++;
            d = max(d, y);
        }
    }

    if(r - l >= m || d - u >= n){
        if(k == 0){
            cout << n * m << endl;
        }
        else{
            cout << 0 << endl;
        }
        return;
    }
    //0-base 
    
    int L = -l, R = m - r - 1, U = -u, D = n - d - 1;

    vector<vector<int>>a(m * 2, vector<int>(n * 2));
    x = m, y = n;
    a[x][y] = 1;
    for(int i = 0;i < s.length();i++){
        if(s[i] == 'L'){
            x++;
        }
        else if(s[i] == 'R'){
            x--;
        }
        else if(s[i] == 'U'){
            y++;
        }
        else if(s[i] == 'D'){
            y--;
        }
        if(x > 0 && y > 0 && x < m * 2 && y < n * 2){
            a[x][y] = 1;
        }
    }

    for(int i = 1;i < m * 2;i++){
        for(int j = 1;j < n * 2;j++){
            a[i][j] = a[i][j] + a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
        }
    }

    auto calc = [&](int i, int j)->int
    { 
        return a[m + R - i][n + D - j] - a[m + L - 1 - i][n + D - j] - a[m + R - i][n + U - 1 - j] + a[m + L -1 - i][n + U - 1 - j];
    };

    int ans = 0;
    //area : x[L, R] y[U, D]
    //hole : offset [m, n]
    int rem = (R - L + 1) * (D - U + 1);
    for(int i = 0;i < m;i++){
        for(int j = 0;j < n;j++){
            int cnt = rem - calc(i, j);
            if(cnt == k)ans++;
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