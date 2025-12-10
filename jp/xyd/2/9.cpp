#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    constexpr int N = 5001;
    int n,k;
    cin>>n>>k;
    vector<vector<ll>>a(N + 1,vector<ll>(N + 1));
    for(int i = 0;i < n;i++){
        int x,y,v;
        cin>>x>>y>>v;
        x++,y++;
        a[x][y] += v;
    }
    for(int i = 1;i <= N;i++){
        for(int j = 1;j <= N - 1;j++){
            a[i][j + 1] += a[i][j];
        }
    }
    for(int i = 1;i <= N - 1;i++){
        for(int j = 1;j <= N;j++){
            a[i + 1][j] += a[i][j];
        }
    }

    int lenl = k / 2, lenr = (k + 1) / 2;

    auto get = [&](int x, int y)->ll
    {
        int lx = max(0,x - lenl - 1), rx = min(N,x + lenr - 1);
        int ly = max(0,y - lenl - 1), ry = min(N,y + lenr - 1);
        //cerr<<lx<<" "<<rx<<" "<<ly<<" "<<ry<<endl;
        return a[rx][ry] - a[rx][ly] - a[lx][ry] + a[lx][ly];
    };

    ll ans = 0;
    for(int i = 1;i <= N;i++){
        for(int j = 1;j <= N;j++){
            ans = max(ans,get(i,j));//center on (i,j)
        }
    }
    cout<<ans<<endl;
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