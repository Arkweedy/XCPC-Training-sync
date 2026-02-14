#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//F.cpp Create time : 2026.02.14 21:38

//matrix ? 
// add and max

using matrix = vector<vector<i64>>;

constexpr i64 inf = 2e18;

matrix operator*(matrix& a, matrix& b)
{
    if(a.empty())return b;
    int n = a.size();
    matrix res = vector<vector<i64>>(n, vector<i64>(n, inf));
    for(int k = 0;k < n;k++){
        for(int j = 0;j < n;j++){
            for(int i = 0;i < n;i++){
                res[i][j] = min(res[i][j], a[i][k] + b[k][j]);
            }
        }
    }
    return res;
}

matrix power(matrix a, int p)
{
    matrix res;
    while(p){
        if(p & 1)res = res * a;
        a = a * a;
        p >>= 1;
    }
    return res;
}

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<vector<i64>>c(n, vector<i64>(n));
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            cin >> c[i][j];
        }
    }
    auto ans = power(c, k);
    for(int i = 0;i < n;i++){
        cout << ans[i][i] << endl;
    }
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