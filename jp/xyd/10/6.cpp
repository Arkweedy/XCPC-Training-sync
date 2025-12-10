#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

int digit(ll x)
{
    int res = 0;
    while(x != 0){
        res += x % 10;
        x /= 10;
    }
    return res;
}

void solve()
{
    ll n;
    cin>>n;
    auto get_solve = [&](int s)->ll
    {
        ll l = 0, r = 1e9+ 10;
        while(r - l > 1){
            ll m = l + r >> 1;
            if(m * m + s * m <= n){
                l = m;
            }
            else{
                r = m;
            }
        }
        if(l * l + s * l == n && digit(l) == s){
            return l;
        }
        else{
            return -1;
        }
    };

    ll ans = 1145141919810ll;
    for(int i = 1;i <= 18*9;i++){
        ll res = get_solve(i);
        if(res != -1){
            ans = min(ans,res);
        }
    }
    if(ans == 1145141919810ll){
        cout<<-1<<endl;
    }else{
        cout<<ans<<endl;
    }
    return;

}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}