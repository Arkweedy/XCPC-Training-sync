#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    constexpr int n = 24;
    constexpr int T = 1e5 / n;
    constexpr int inf = 1e9;
    constexpr int up = 91;
    cout<<T<<endl;
    for(int i = 0;i < T;i++){
        cout<<n<<' '<<5<<endl;
        vector<pair<int,int>>  ve;
        for(int j = 0;j < 6;j++){
            ve.push_back({1<<j,inf-j});
            ve.push_back({3*(1<<j),inf-j});
            //cout<<(1<<j)<<" "<<inf - j<<endl;
        }
        for(auto [x,y]:ve) cout<<x<<' '<<y<<'\n';
        for(auto [x,y]:ve) cout<<y<<' '<<x<<'\n';
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