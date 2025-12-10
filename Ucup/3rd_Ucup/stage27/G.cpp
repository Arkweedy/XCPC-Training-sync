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
    int x = 9, y = 16;
    int z = (n + 8) / x;
    vector<vector<int>>a(n,vector<int>(n));
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            a[i][j] = (i / 16) * z + (j / 9) + 1;
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
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}