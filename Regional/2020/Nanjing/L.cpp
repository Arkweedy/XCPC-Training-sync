#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using i128 = __int128;
using namespace std;


void solve()
{
    ll n,m;cin>>n>>m;
    cout<<fixed<<setprecision(15);
    if(gcd(n,m) == 1){
        cout<<hypotl(n,m)<<'\n';
    }else{
        long double res = 1e18;
        ll Bx = sqrtl(n),By = sqrtl(m);
        
        for(ll i=0;i<=n;i++){
            ll p = i * m / n;
            ll j = p;
            while(j<=m &&((i*(m-j)==j*(n-i)) || gcd(i,j)!=1 || gcd(n-i,m-j) != 1)) j++;
            if(j<=m){
            
                res = min(res,hypotl(i,j)+hypotl(n-i,m-j));
            }
            j = p;
            while(j>=0 && ((i*(m-j)==j*(n-i))||gcd(i,j) != 1 || gcd(n-i,m-j) != 1))j--;
            if(j>=0){
        
                res = min(res,hypotl(i,j)+hypotl(n-i,m-j));
            }
        }
        cout<<res<<'\n';
    }
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