#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    ll n,k,s,t;
    cin>>n>>k>>s>>t;
    ll dis = abs(s - t);
    if(k % 2 == 0 && dis % 2 == 1){
        cout<<-1<<endl;
        return;
    }
    if(s == t){
        cout<<0<<endl;
        return;
    }

    ll inf = 1145141919810;
    ll ans = inf;
    ll r = min(k * 2, (n - k) * 2);
    
    //even
    //cerr<<"even dis : "<<dis<<endl;
    if(dis % 2 == 0 && r != 0){
        ans = min(ans, (dis + r - 1) / r * 2);
    }
   
    //odd
    if(dis % 2 == k % 2){
        ll mi = abs(s - k),ma = min(s + k, n * 2 - k - s);
        if(mi <= t && t <= ma){
            dis = 0;
        }
        else if(t > ma){
            dis = t - ma;
        }
        else{
            dis = mi - t;
        }

        //cerr<<"odd min dis : "<<dis<<endl;
        if(dis == 0)ans = min(ans,1ll);
        if(dis % 2 == 0 && r != 0){
            ans = min(ans, (dis + r - 1) / r * 2 + 1);
        }
    }

    if(ans == inf)ans = -1;
    cout<<ans<<endl;
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