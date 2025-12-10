#include<bits/stdc++.h>

using ll = long long;
using namespace std;
using ld = long double;

constexpr int N = 1e5 + 10;

void solve()
{
    int n,m;
    cin>>n>>m;
    vector<vector<ld>>a(n,vector<ld>(m));

    if(n >= m * 2){
        for(int i = 0;i < m * 2;i++){
            a[i][m-i/2-1] = 1;
        }
        for(int i = 2*m;i < n;i++){
            a[i][0] = 1;
        }
    }
    else if(n % 2 == 0){
        for(int i = 0;i < n;i++){
            a[i][m-i/2-1] = 1;
        }
    }
    else{
        for(int i = 0;i < n;i++){
            a[i][m-i/2-1] = 1;
        }
    }

    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            cout<<fixed<<setprecision(12)<<a[i][j]<<" ";
        }
        cout<<endl;
    }
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}