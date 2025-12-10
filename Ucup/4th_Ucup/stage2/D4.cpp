#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e5 + 10;

ll digit(ll n)
{
    int res = 0;
    while(n != 0){
        res += n % 10;
        n /= 10;
    }
    return res;
}

void solve()
{
    int n;cin>>n;
    vector<int>vis(2000);
    int ma = 0;
    vector<int>dp(n + 1, 0);
    
    vector<pair<ll,ll>>pre(n+1);
    dp[0] = 1;
    int i = 1;
    while(1){
        ll x = 1ll *  n * i;
        int d = digit(x);
        if(vis[d]){
            i++;
            continue;
        }
        vis[d] = 1;
        for(int j = 0;j + d <= n;j++){
            if(dp[j] && !dp[j+d]){
                dp[j+d] = 1;
                pre[j+d] = {j,x};
            }
        }
        if(dp[n])break;
        i++;
    }
    string s;
    while(n){
        auto [x,y] = pre[n];
        s += to_string(y);
        n = x;
    }
    cout<<s<<'\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}