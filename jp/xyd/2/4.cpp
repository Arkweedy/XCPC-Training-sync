#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,m;
    cin>>n>>m;
    vector<vector<int>>a(n + 1,vector<int>(n + 1));
    for(int i = 0;i < m;i++){
        int x,y,u,v;
        cin>>x>>y>>u>>v;
        x--,y--,u--,v--;
        a[x][y]++;
        a[x][v+1]--;
        a[u+1][y]--;
        a[u+1][v+1]++;
    }
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n - 1;j++){
            a[i][j + 1] += a[i][j];
        }
    }
    for(int i = 0;i < n - 1;i++){
        for(int j = 0;j < n;j++){
            a[i + 1][j] += a[i][j];
        }
    }
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }
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