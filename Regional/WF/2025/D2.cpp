#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.12.25 15:00:43

void solve()
{
    int r, c;
    cin >> r >> c;
    vector<string>a(r);
    for(int i = 0;i < r;i++){
        cin >> a[i];
    }
    string s;
    cin >> s;

    int sx, sy;
    for(int i = 0;i < r;i++){
        for(int j = 0;j < c;j++){
            if(a[i][j] == 'S'){
                sx = i;
                sy = j;
            }
        }
    }

    vector<int>d = {0,1,2,3};
    vector<int>dx = {0,1,0,-1}, dy = {1,0,-1,0};
    vector<char>C = {'E','S','W','N'};
    map<char, int>mp;
    mp['E'] = 0;
    mp['S'] = 1;
    mp['W'] = 2;
    mp['N'] = 3;

    auto ok = [&](int x, int y)->bool
    {
        if(x >= 0 && x < r && y >= 0 && y < c && a[x][y] != '#')return true;
        else return false;
    };
    vector<vector<int>>p;
    do{
        p.push_back(d);
    }while(next_permutation(d.begin(), d.end()));

    int x = sx, y = sy;
    auto check = [&](int i, char dir)->bool
    {
        for(auto j : p[i]){
            int nx = x + dx[j], ny = y + dy[j];
            if(ok(nx, ny)){
                if(C[j] != dir)return false;
                else return true;
            }
        }

        return false;
    };
    
    constexpr int inf = 1e9;
    s = ' ' + s;
    int n = s.length();
    vector<array<int,24>>dp(n);
    dp[0].fill(0);
    for(int i = 1;i < n;i++){
        vector<int>okd, ned;
        for(int j = 0;j < 24;j++){
            if(check(j, s[i]))okd.push_back(j);
            else ned.push_back(j);
        }
        int v = inf;
        for(int j = 0;j < 24;j++){
            v = min(v, dp[i - 1][j]);
        }
        for(auto j : okd){
            dp[i][j] = min(dp[i - 1][j], v + 1);
        }
        for(auto j : ned){
            dp[i][j] = inf;
        }
        int t = mp[s[i]];
        x = x + dx[t], y = y + dy[t];
    }
    int ans = inf;
    for(int i = 0;i < 24;i++){
        ans = min(ans, dp[n - 1][i]);
    }
    cout << ans << endl;
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