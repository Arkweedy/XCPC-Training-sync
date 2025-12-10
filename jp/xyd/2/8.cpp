#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,m,k;
    cin>>n>>m>>k;
    vector<vector<int>>a(n + 1,vector<int>(m + 1)),b(n + 1,vector<int>(m + 1));
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            cin>>a[i][j];
        }
    }
    for(int i = 0;i < k;i++){
        int x,y,u,v;
        cin>>x>>y>>u>>v;
        x--,y--,u--,v--;
        b[x][y] ^= 1;
        b[x][v + 1] ^= 1;
        b[u + 1][y] ^= 1;
        b[u + 1][v + 1] ^= 1;
    }
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m - 1;j++){
            b[i][j + 1] ^= b[i][j];
        }
    }
    for(int i = 0;i < n - 1;i++){
        for(int j = 0;j < m;j++){
            b[i + 1][j] ^= b[i][j];
        }
    }
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            a[i][j] ^= b[i][j];
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
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