#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int P = 1000000007;

int power(int a, int p)
{
    int res = 1;
    while(p){
        if(p & 1)res = 1ll * res * a % P;
        a = 1ll * a * a % P;
        p >>= 1;
    }
    return res;
}

//100pts
void solve()
{
    int n,k;
    cin>>n>>k;
    ll ans = 0;
    vector<int>ak(n + 1);
    for(int i = 1;i <= n;i++){
        ak[i] = power(i, k);
    }
    vector<ll>f(n + 1);
    for(int i = 1;i <= n;i++){
        for(int j = 1;j * i <= n;j++){
            f[i * j] += ak[i];
        }
    }
    for(int i = 1;i <= n;i++){
        ans += f[i];
    }
    ans %= P;
    cout<<ans<<endl;
    return;
}

int main()
{
    // freopen("yoshiko.in","r",stdin);
    // freopen("yoshiko.out","w",stdout);
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}