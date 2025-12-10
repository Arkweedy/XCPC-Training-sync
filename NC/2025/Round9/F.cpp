#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    ll sx1,sy1,sx2,sy2,tx1,ty1,tx2,ty2;
    cin>>sx1>>sy1>>sx2>>sy2>>tx1>>ty1>>tx2>>ty2;

    ll sx = (sx1 + sx2 + sy1 + sy2) , sy = (sx1 + sx2 - sy1 - sy2);
    ll tx = (tx1 + tx2 + ty1 + ty2) , ty = (tx1 + tx2 - ty1 - ty2);
    cout<<(abs(sx - tx) + abs(sy - ty)) / 2<<"\n";


    // if((sx1 + sy1) % 2 == 1){
    //     swap(sx1,sx2);
    //     swap(sy1,sy2);
    // }
    // if((tx1 + ty1) % 2 == 1){
    //     swap(tx1,tx2);
    //     swap(ty1,ty2);
    // }

    // int xy1 = (sx1 == sx2), xy2 = (tx1 == tx2);//0 -  1 |
    // auto dis = [](int x1, int y1,int x2, int y2)->int
    // {
    //     return max(abs(x1 - x2), abs(y1 - y2));
    // };
    // ll sdis = dis(sx1,sy1,tx1,ty1) +  dis(sx2,sy2,tx2,ty2);
    // ll ans = sdis;
    
    // cout<<ans<<"\n";
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