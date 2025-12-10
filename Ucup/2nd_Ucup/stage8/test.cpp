#include<bits/stdc++.h>

using namespace std;

using ll = long long;

constexpr ll INF = 1e18;
constexpr int mod = 1e9 + 7;
constexpr int N = 1e5 + 10;

void solve()
{
    int ans=1;
    for(int i=1;i<=7;i++) ans*=i;
    cout<<ans;
}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int t = 1;
   // cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
