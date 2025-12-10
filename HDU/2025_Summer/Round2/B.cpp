#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

ll lowbit(ll x)
{
    return x & -x;
}

void solve()
{
    ll n, x, y;
    cin>>n>>x>>y;
    if(lowbit(x) == lowbit(y) || __popcount(x) == __popcount(y)){
        cout<<1<<endl;
    }
    else{
        cout<<2<<endl;
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