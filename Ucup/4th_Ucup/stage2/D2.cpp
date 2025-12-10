#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e5 + 10;

int digit(ll n)
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
    //int n;
    //cin>>n;
    int ma = 0;
    for(int n = 1;n <= 200000;n++){
        vector<int>dp(n + 1, -1);
        vector<pair<int,int>>pre(n + 1, -1);//prepos, i
        dp[0] = 1;
        for(int i = 1;i <= n;i++){
            ll x = n * i;
            int d = digit(x);
            for(int j = 0;j + d <= n;j++){
                if(dp[j + d] != 1 && dp[j]){
                    dp[j + d] = 1;
                    pre[j + d] = {j, i};
                }
            }
            if(dp[n] == 1){
                if(i > 100)
                cout<<n<<" "<<i<<endl;
                break;
            }
        }
    }
    return;
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