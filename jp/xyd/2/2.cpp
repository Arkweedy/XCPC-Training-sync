#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,m,q;
    cin>>n>>m>>q;
    vector<vector<int>>a(n + 1,vector<int>(m + 1));
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            cin>>a[i][j];
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m - 1;j++){
            a[i][j + 1] += a[i][j];
        }
    }
    for(int i = 1;i <= n - 1;i++){
        for(int j = 1;j <= m;j++){
            a[i + 1][j] += a[i][j];
        }
    }
    while(q--){
        int x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        cout<<a[x2][y2] - a[x1-1][y2] - a[x2][y1-1] + a[x1-1][y1-1]<<endl;
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