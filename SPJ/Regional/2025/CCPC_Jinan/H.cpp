#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e5 + 10;
int f[N];
constexpr int  mod=1e9+7;
void solve()
{
    f[1]=1;f[0]=1;
    for(int i=2;i<=20;i++)
    {
    //    cout<<i<<endl;return ;
        for(int j=0;j<=i-1-j;j++) f[i]=(f[i]+1ll*f[j]*f[i-1-j])%mod;
        cout<<i<<' '<<f[i]<<endl;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
//    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}
