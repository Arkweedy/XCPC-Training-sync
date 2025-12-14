#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e5 + 10;

void solve()
{
    int n;
    cin>>n;
    cout<<n*(n + 1) / 2<<endl;
    for(int i = 0;i < n;i++){
        cout<<n - i<<" ";
    }
    cout<<endl;
    return;
}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int tt = 1;
    //cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}
