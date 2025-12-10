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
    int g = gcd(n,m);
    if(g != 1){
        cout<<"NO"<<endl;
        return;
    }
    cout<<"YES"<<endl;
    vector<vector<int>>a(n,vector<int>(m));
    int x = 0, y = 0;
    int fx = 1,fy = 1;
    for(int i = 1;i <= n * m;i++){
        a[x][y] = i;
        if(i % n == 0){
            y = (y + i * fy % m + m) % m;
            fy = -fy;
        }
        else{
            x = (x - i * fx % n + n) % n;
            fx = -fx;
        }
    }

    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
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