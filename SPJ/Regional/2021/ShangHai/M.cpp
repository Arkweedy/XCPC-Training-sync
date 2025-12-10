#include<bits/stdc++.h>

using ll = long long;

using namespace std;

constexpr int N = 1e5 + 10;
ll n;
void solve()
{
    cin>>n;
    
    long double ans = 1.0 /(n*n);
    for(int i=1;i<=n;i++)ans = min(ans,(long double)1.0/(n*i)/(n-i+1));

    cout<<fixed<<setprecision(9)<<ans;

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