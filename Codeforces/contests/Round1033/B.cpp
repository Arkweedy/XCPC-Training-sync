#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n, s;
    cin>>n >> s;
    int ans = 0;
    for(int i = 0;i < n;i++){
        int x,y,vx,vy;
        cin>>vx>>vy>>x>>y;
        if(vx * vy == 1){
            if(x == y){
                ans++;
            }
        }else{
            if(x + y == s){
                ans++;
            }
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
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}