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
    vector<vector<int>>a(n,vector<int>(m));
    auto ok = [&](int x, int y)->bool
    {
        return x >= 0 && y >= 0 && x < n && y < m;
    };
    auto clr = [&](int x, int y, int c)->void
    {
        if(ok(x,y))a[x][y] = c;
        if(ok(x-1,y))a[x-1][y] = c;
        if(ok(x-2,y))a[x-2][y] = c;
        if(ok(x-3,y))a[x-3][y] = c;
        if(ok(x-4,y))a[x-4][y] = c;
        if(ok(x-2,y-1))a[x-2][y-1] = c;
        if(ok(x-2,y-2))a[x-2][y-2] = c;
        if(ok(x-2,y+1))a[x-2][y+1] = c;
        if(ok(x-2,y+2))a[x-2][y+2] = c;
        if(ok(x-3,y+1))a[x-3][y+1] = c;
        if(ok(x-3,y-1))a[x-3][y-1] = c;
    };

    vector<pair<int,int>>xy(k);
    for(int i = 1;i <= k;i++){
        int x,y;
        cin>>x>>y;
        x--,y--;
        clr(x,y,i);
    }

    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            if(a[i][j] == 0)cout<<'.';
            else cout<<a[i][j];
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
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}