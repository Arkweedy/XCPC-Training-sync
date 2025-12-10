#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n;
    array<int,4>c;
    cin>>c[0]>>c[1]>>c[2]>>c[3]>>n;
    constexpr int N = 1e5;
    vector<ll>dp(N + 1);
    dp[0] = 1;
    for(int i = 0;i < 4;i++){
        for(int j = c[i];j <= N;j++){
            dp[j] += dp[j - c[i]];
        }
    }

    while(n--){
        int s;
        array<int,4>d;
        cin>>d[0]>>d[1]>>d[2]>>d[3]>>s;
        ll ans = 0;
        
        for(int i = 0;i < 16;i++){
            int p = s,k = 1;
            for(int j = 0;j < 4;j++){
                if(i >> j & 1){
                    p -= (d[j] + 1) * c[j];
                    k *= -1;
                }
            }
            if(p >= 0){
                ans += dp[p] * k;
            }
        }
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