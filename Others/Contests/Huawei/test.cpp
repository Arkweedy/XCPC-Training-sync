#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//test.cpp Create time : 2026.05.21 09:42

struct DSU{
    int n;
    vector<int>fa, sz;
    int scc;

    DSU(int n_) : n(n_), fa(n),sz(n, 1), scc(n){
        iota(fa.begin(),fa.end(), 0);
    }

    int find(int p)
    {
        return fa[p] == p ? p : (fa[p] = find(fa[p]));
    }

    void merge(int u, int v)
    {
        int fu = find(u), fv = find(v);
        if(fu == fv)return;
        if(sz[fu] < sz[fv])swap(fu, fv);
        fa[fv] = fu;
        sz[fu] += sz[fv];
        scc--;
        return;
    }
};

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();
        DSU dsu(n * m);
        int cnt0 = 0;
        for(int i = 0;i < m;i++){
            for(int j = 0;j < n;j++){
                if(grid[i][j] == '0'){
                    cnt0++;
                }
                else{
                    if(i < m - 1 && grid[i + 1][j] == '1'){
                        dsu.merge(i * n + j, (i + 1) * n + j);
                    }
                    if(j < n - 1 && grid[i][j + 1] == '1'){
                        dsu.merge(i * n + j, i * n + j + 1);
                    }
                }
            }
        }
        int ans = dsu.scc - cnt0;
        return ans;
    }
};

int numIslands(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();
        DSU dsu(n * m);
        int cnt0 = 0;
        for(int i = 0;i < m;i++){
            for(int j = 0;j < n;j++){
                if(grid[i][j] == '0'){
                    cnt0++;
                }
                else{
                    if(i < m - 1 && grid[i + 1][j] == '1'){
                        dsu.merge(i * n + j, (i + 1) * n + j);
                    }
                    if(j < n - 1 && grid[i][j + 1] == '1'){
                        dsu.merge(i * n + j, i * n + j + 1);
                    }
                }
            }
        }
        int ans = dsu.scc - cnt0;
        return ans;
    }


void solve()
{
    vector<vector<char>>t = {
        {'1','1','1','1','0'},
        {'1','1','0','1','0'},
        {'1','1','0','0','0'},
        {'0','0','0','0','0'}
    };
    vector<vector<char>>t2 = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    int ans = numIslands(t2);
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