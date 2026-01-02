#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//P2455.cpp Create time : 2026.01.02 11:38

void solve()
{
    int n;
    cin >> n;
    vector<vector<double>>a(n,vector<double>(n + 1));
    for(int i = 0;i < n;i++){
        for(int j = 0;j <= n;j++){
            int x;
            cin >> x;
            a[i][j] = x;
        }
    }
    constexpr double eps = 1e-7;

    auto z = [&](double x)->bool
    {
        return abs(x) <= eps;
    };

    //REF row echelon form
    for(int i = 0;i < n;i++){
        if(a[i][i] == 0 || abs(a[i][i]) <= eps){
            for(int j = i + 1;j < n;j++){
                if(a[j][i] != 0 && abs(a[j][i]) >= eps){
                    swap(a[i], a[j]);
                    break;
                }
            }
        }
        if(a[i][i] != 0){
            for(int j = i + 1;j < n;j++){
                double c = a[j][i] / a[i][i];
                for(int k = i; k <= n; k++){
                    a[j][k] -= c * a[i][k];
                }
            }
        }
    }

    

    vector<double>ans(n, -1);
    int ok = 1;
    for(int i = n - 1;i >= 0;i--){
        int p = -1;
        for(int j = i;j < n;j++){
            if(!z(a[i][j])){
                p = j;
            }
        }
        if(p != -1){
            ans[p] = a[i][n] / a[i][p];
            for(int j = 0;j < i;j++){
                a[j][n] -= a[j][p] * ans[p];
                a[j][p] = 0;
            }
        }
        else if(!z(a[i][n])){
            ok = -1;
        }
        else{
            ok = min(ok, 0);
        }
    }

    // cerr <<"ok = " << ok << endl; 

    // for(int i = 0;i < n;i++){
    //     for(int j = 0;j <= n;j++){
    //         cerr << a[i][j] << " ";
    //     }
    //     cerr << endl;
    // }

    if(ok == 1){
        for(int i = 0;i < n;i++){
            cout << "x" << i << "=" << fixed << setprecision(7) << ans[i] << endl;
        }
    }
    else{
        cout << ok << endl;
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