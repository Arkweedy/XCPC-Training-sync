#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

vector<int>sz(100,1);
vector<vector<int>>g;

voif dfs(int p, int fa)
{
    for(auto s : g[p]){
        if(s != fa){
            dfs(s, p);
            sz[p] += sz[s];
        }
    }
};

void solve()
{
    int root = 1;
    dfs(root,-1);
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