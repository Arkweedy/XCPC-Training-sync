#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n;
    cin>>n;
    vector<int>f(n);
    for(int i = 0;i < n;i++){
        cin>>f[i];
    }
    vector<vector<int>>a(n,vector<int>(n));
    for(int i = 0;i < n;i++){
        vector<int>res(i + 1);
        for(int j = 0;j + 2 < f[i];j++){
            res[j] = j + 2;
        }
        if(f[i] > 1)res[i] = 1;
        for(int j = 0;j <= i;j++){
            a[i][j] = res[j];
            a[j][i] = res[j];
        }
    }

    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            cout<<a[i][j]<<" ";
        }
        cout<<"\n";
    }
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