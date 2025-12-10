#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.10.31 16:37:10
constexpr int P = 998244353;
int power(int a, int p)
{
    int res = 1;
    while(p){
        if(p & 1)res = 1ll * res * a % P;
        a = 1ll * a * a % P;
        p >>= 1;
    }
    return res;
}

void solve()
{
    int n, m;
    cin>>n>>m;
    vector<int>c(n * m + 1);
    vector<vector<int>>a(n,vector<int>(m));
    vector<vector<pair<int,int>>>pos(n * m + 1);
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            cin>>a[i][j];
            c[a[i][j]]++;
            pos[a[i][j]].emplace_back(i, j);
        }
    }
    int sq = sqrt(n * m);

    ll ans = 0;
    vector<int>fac(n * m + 1),invfac(n * m + 1);
    fac[0] = invfac[0] = 1;
    for(int i = 1;i <= n * m;i++){
        fac[i] = 1ll * fac[i - 1] * i % P;
    }
    invfac[n * m] = power(fac[n * m], P - 2);
    for(int i = n * m;i >= 1;i--){
        invfac[i - 1] = 1ll * invfac[i] * i % P;
    }

    auto path = [&](int x, int y)->int
    {
        if(x < 0 || y < 0)return 0;
        return 1ll * fac[x + y] * invfac[x] % P * invfac[y] % P;
    };  

    for(int i = 1;i <= n * m;i++){
        if(c[i] < sq){
            sort(pos[i].begin(),pos[i].end(),[&](pair<int,int>i,pair<int,int>j)->bool
            {
                return i.first + i.second < j.first + j.second; 
            });
            int k = pos[i].size();
            vector<int>f(k);
            for(int j = 0;j < k;j++){
                auto [x, y] = pos[i][j];
                f[j] = path(x, y);
            }
            for(int j = 0;j < k;j++){
                auto [jx, jy] = pos[i][j];
                for(int s = j + 1;s < k;s++){
                    auto [sx,sy] = pos[i][s];
                    f[s] = (f[s] - 1ll * f[j] * path(sx - jx, sy - jy) % P + P) % P; 
                }
            }
            for(int j = 0;j < k;j++){
                auto [x, y] = pos[i][j];
                ans = (ans + 1ll * f[j] * path(n - 1 - x, m - 1 - y)) % P; 
            }
        }
        else{
            
            vector<vector<int>>f(n + 1,vector<int>(m + 1));
            f[0][0] = 1;
            for(int j = 0;j < n;j++){
                for(int k = 0;k < m;k++){
                    if(a[j][k] != i){
                        f[j + 1][k] += f[j][k];
                        if(f[j + 1][k] > P)f[j + 1][k] -= P;
                        f[j][k + 1] += f[j][k];
                        if(f[j][k + 1] > P)f[j][k + 1] -= P;
                    }
                }
            }
            for(auto [x, y] : pos[i]){
                ans = (ans + 1ll * f[x][y] * path(n - 1 - x, m - 1 - y)) % P;
            }
        }
    }

    cout<<ans<<endl;
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