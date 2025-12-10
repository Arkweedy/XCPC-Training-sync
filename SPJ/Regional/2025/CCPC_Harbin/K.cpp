#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e5 + 10;
constexpr int P = 1e9 + 7;
int n;
int a[N];
void solve()
{
    cin>>n;
    cout<<n<<'\n';
    a[1]=n;a[2]=n+1;
    for(int i=3;i<=n;i++) a[i]=a[1]+a[i-1]+1;
    for(int i=1;i<=n;i++) cout<<i<<' ';
    cout<<'\n';
    for(int i=1;i<=n;i++) cout<<a[i]<<' ';
    cout<<'\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}