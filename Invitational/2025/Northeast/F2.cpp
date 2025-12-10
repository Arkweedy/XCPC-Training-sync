#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int a,b,c,d,e,f;
    cin>>a>>b>>c>>d>>e>>f;
    int t1 = c * 60 + d,t2  = e * 60 + f;
    int t0 = a * 60 + b;
    assert(t1 <= t2);
    array<int,3>ans = {114514,-1,-1};
    for(int i = t1;i <= t2;i++){
        int x = i / 60,y = i % 60;
        int d = min((t0 - i + 720) % 720, (i - t0 + 720) % 720) + min((b - y + 60) % 60, (y - b + 60) % 60) * 12;
        if(d < ans[0]){
            ans = {d,x,y};
        }
    }
    cout<<ans[1]<<" "<<ans[2]<<endl;
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