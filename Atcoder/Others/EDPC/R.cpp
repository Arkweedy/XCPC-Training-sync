#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.07.16 11:13:33

constexpr int P = 1e9 + 7;

using matrix = vector<vector<int>>;

matrix operator*(matrix& A, matrix& B)
{
    int n = A.size();
    matrix res(n, vector<int>(n));
    for(int k = 0;k < n;k++){
        for(int i = 0;i < n;i++){
            for(int j = 0;j < n;j++){
                res[i][j] = (res[i][j] + 1ll * A[i][k] * B[k][j]) % P;
            }
        }
    }
    return res;
}

matrix I(int n)
{
    matrix res(n, vector<int>(n));
    for(int i = 0;i < n;i++){
        res[i][i] = 1;
    }
    return res;
}

void solve()
{
    int n;
    i64 k;
    cin >> n >> k;
    vector<vector<int>>a(n, vector<int>(n));
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            cin >> a[i][j];
        }
    }

    matrix A = I(n);
    while(k){
        if(k & 1)A = A * a;
        a = a * a;
        k >>= 1;
    }
    i64 ans = 0;
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            ans += A[i][j];
        }
    }
    ans %= P;
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