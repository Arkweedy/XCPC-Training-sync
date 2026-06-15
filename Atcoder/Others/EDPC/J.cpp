#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.06.15 15:04:44

using ld = long double;

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    vector<int>c(4);
    for(int i = 0;i < n;i++){
        cin >> a[i];
        c[a[i]]++;
    }
    int x = c[3], y = c[2], z = c[1];
    
    vector<vector<vector<ld>>>P(x + 1, vector<vector<ld>>(x + y + 1, vector<ld>(n + 1, 0)));
    P[x][y][z] = 1;
    auto add = [&](int i, int j, int k, ld Pr)->void
    {
        P[i][j][k] += Pr;
    };
    ld ans = 0;
    for(int i = x;i >= 0;i--){
        for(int j = x + y - i;j >= 0;j--){
            for(int k = n - i - j;k >= 0;k--){
                int sum = i + j + k;
                if(sum == 0)continue;
                ans += P[i][j][k] * n / sum;
                if(i > 0)add(i - 1, j + 1, k, P[i][j][k] * ld(i) / sum);
                if(j > 0)add(i, j - 1, k + 1, P[i][j][k] * ld(j) / sum);
                if(k > 0)add(i, j, k - 1, P[i][j][k] * ld(k) / sum);
            }
        }
    }
    cout << fixed << setprecision(10) << ans << endl;
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