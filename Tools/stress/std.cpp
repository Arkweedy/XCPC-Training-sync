#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//F2.cpp Create time : 2026.02.12 00:39

//O(n^3)

//二维平面上的游走？
// 每次存在一个方向cost = 0
// 只能在第一象限， 且最后必须回到零点
// 什么时候可以把两维拆开考虑？
// 
// guess， 最多一次 x <-> y, 当且仅当 均为奇数次操作？ 好像有hack （test 1.5）
// 


// 如果只有一种括号，可以直接O(n)贪心
// 只在必要的时候修改， 好像无法保证最优性

// 使用DS优化dp? 
// 不太想得到合适的DS

// 二分答案， O(n)/O(nlogn) check ? 


void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    map<pair<int,int>, int>dp;
    dp[{0, 0}] = 0;
    // () []
    vector<int>dx = {1, -1, 0, 0}, dy = {0, 0, 1, -1};
    vector<int>alp(256);
    alp['('] = 0;
    alp[')'] = 1;
    alp['['] = 2;
    alp[']'] = 3;
    for(int i = 0;i < n;i++){
        map<pair<int,int>, int>ndp;
        int c = alp[s[i]];
        for(int j = 0;j < 4;j++){
            int cost = j == c ? 0 : 1;
            for(auto [pr, mc] : dp){
                auto [x, y] = pr;
                int nx = x + dx[j], ny = y + dy[j], nc = mc + cost;
                if(nx >= 0 && ny >= 0){
                    if(ndp.count({nx,ny}))ndp[{nx,ny}] = min(ndp[{nx,ny}], nc);
                    else ndp[{nx,ny}] = nc;
                }
            }
        }
        dp = move(ndp);
    }

    cout << dp[{0, 0}] << endl;
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