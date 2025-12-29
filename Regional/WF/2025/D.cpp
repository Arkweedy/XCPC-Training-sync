#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.12.25 14:21:34

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
    
    auto walk = [&](vector<int>d)->int
    {
        int x = sx, y = sy;
        int cnt = 0;
        for(auto ch : s){
            for(auto i : d){
                int nx = x + dx[i], ny = y + dy[i];
                if(ok(nx, ny)){
                    if(C[i] != ch)cnt++;
                    break;
                }
            }
            int t = mp[ch];
            x = x + dx[t], y = y + dy[t];
        }
        cerr << cnt << endl;
        return cnt;
    };

    int ans = walk(d);
    while(next_permutation(d.begin(),d.end())){
        ans = min(ans, walk(d));
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