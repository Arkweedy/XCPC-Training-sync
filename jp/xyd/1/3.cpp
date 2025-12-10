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
    vector<vector<int>>a(n,vector<int>(m));
    for(int i = 0;i < n;i++){
        for(int j= 0;j < m;j++){
            cin>>a[i][j];
        }
    }
    while(q--){
        int i,j;
        cin>>i>>j;
        
        cout<<a[i][j]<<endl;
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