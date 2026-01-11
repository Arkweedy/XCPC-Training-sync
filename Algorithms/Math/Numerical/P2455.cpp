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

    //REF
    int r = 0;
    for(int i = 0; i < n; i++){
        //find 
        for(int j = r;j < n;j++){
            if(!z(a[j][i])){
                swap(a[r], a[j]);
            }
        }
        if(z(a[r][i]))continue; // col i all 0
        for(int j = 0;j < n;j++){
            if(j != r){
                double c = a[j][i] / a[r][i];
                for(int k = 0;k <= n;k++){
                    a[j][k] -= a[r][k] * c;
                }
            }
        }
        r++;
    }

    vector<double>ans(n, -1);
    int multi = 0, none = 0;
    for(int i = 0;i < n;i++){
        int all0 = 1;
        int p = -1;
        for(int j = 0;j < n;j++){
            if(!z(a[i][j])){
                all0 = 0;
                 p = j;
                break;
            }
        }
        if(all0){
            if(z(a[i][n]))multi = 1;
            else none = 1;
        }
        else{
            ans[p] = a[i][n] / a[i][p];
            for(int j = p + 1;j < n;j++){
                if(!z(a[i][j]))ans[i] = 0;
            }
        }
    }

    if(none){
        cout << -1 << endl;
    }
    else if(multi){
        cout << 0 << endl;
    }
    else{
        cout << fixed << setprecision(7);
        for(int i = 0;i < n;i++){
            cout << "x" << i + 1 << "=" << ans[i] << endl;
        }
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