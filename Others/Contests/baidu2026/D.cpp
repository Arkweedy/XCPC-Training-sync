#include<bits/stdc++.h>

using i64 = long long;

using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<vector<i64>>a(n + 1, vector<i64>(n + 1));
    for(int i = 1;i <= n;i++){
        for(int j = i;j <= n;j++){
            cin >> a[i][j];
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            a[i][j] += a[i - 1][j];
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= n;j++){
            a[i][j] += a[i][j - 1];
        }
    }

    // for(int i = 1;i <= n;i++){
    //     for(int j = 1;j <= n;j++){
    //         cerr << a[i][j] << " ";
    //     }
    //     cerr << endl;
    // }
    // cerr << endl;

    auto w = [&](int i, int j)->i64
    {
        i64 ans = a[j][n] - a[j][j - 1] - a[i][n] + a[i][j - 1] * 2 - a[i][i - 1];
        return ans;
    };

    // a < b < c < d
    // w(a, b) + w(c, d) < w(a, c) + w(b, d)

    // f(i, j) = min min_k(f(i,k) + f(k, j)) , f(i + 1, j - 1) + w(i, j)
    vector<vector<i64>>f(n + 1, vector<i64>(n + 1));
    for(int k = 2;k <= n;k += 2){
        for(int i = 1;i + k - 1 <= n;i++){
            f[i][i + k - 1] = f[i + 1][i + k - 1 - 1] + w(i, i + k - 1);
            for(int j = 2;j < k;j += 2){
                f[i][i + k - 1] = min(f[i][i + k - 1], f[i][i + j - 1] + f[i + j][i + k - 1]);
            }
        }
    }
    i64 ans = f[1][n];
    cout << ans << endl;
    return;

    // i64 ans = 0;
    //cerr << get(1, 2) << " " << get(3, 4) << " " << get(5, 6) << endl;
    // for(int i = 1;i <= n;i += 2){
    //     ans += get(i, i + 1);
    // }
    // cout << ans << endl;
    // vector<int>p(n);
    // iota(p.begin(),p.end(), 1);
    // do{
    //     int ok = 1;
    //     for(int i = 0;i < n;i += 2){
    //         if(p[i] > p[i + 1])ok = 0;
    //     }
    //     if(ok){
    //         cerr << "###" << endl;
    //         for(int i = 0;i < n;i++){
    //             cerr << p[i] << ' ';
    //         }
    //         cerr << endl;
    //         int x = 0;
    //         for(int i = 0;i < n;i += 2){
    //             cerr << get(p[i], p[i + 1]) << " ";
    //             x += get(p[i], p[i + 1]);
    //         }
    //         cerr << endl;
    //         cerr << x << endl;
    //     }
    // }while(next_permutation(p.begin(), p.end()));

    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}