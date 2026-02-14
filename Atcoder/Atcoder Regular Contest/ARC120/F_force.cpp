#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//F_force.cpp Create time : 2026.02.12 20:53

constexpr int P = 998244353;
void solve()
{
    int n, k, d;
    cin >> n >> k >> d;
    vector<int>a(n);
    for(int i =  0;i < n;i++){
        cin >> a[i];
    }
    vector<vector<int>>f(n + 1, vector<int>(k + 1));
    //f[0][0] = 1; //f[-1][0] = 1
    for(int i = 0;i <= n;i++){
        f[i][0] = 1;
    }
    for(int i = 1;i <= n;i++){
        for(int j = 0;j <= k;j++){
            if(i - 2 >= 0 && j - 1 >= 0)f[i][j] += f[i - 2][j - 1];
            else if(i - 2 == -1 && j - 1 == 0)f[i][j] += 1;
            //if(i - 1 >= 0)f[i][j] += f[i - 1][j];
            //f[i][j] = f[i - 2][j - 1] + f[i - 1][j];
        }
    }

    for(int i = 0;i <= k;i++){
        for(int j = 0;j <= n;j++){
            cerr << f[j][i] << " ";
        }
        cerr << endl;
    }

    i64 ans = 0;
    for(int i = 0;i < n;i++){
        i64 c = 0;
        for(int j = 1;j <= k;j++){
            c += 1ll * f[i + 1][j] * f[n - i][k - j + 1];
        }
        ans += c * a[i];
        cerr << c << endl;
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