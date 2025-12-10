#include<bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
using uint = unsigned int;

using namespace std;

void solve()
{
    int n ,m;
    cin>>n>>m;
    cout<<max(n-m,1)<<endl;
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