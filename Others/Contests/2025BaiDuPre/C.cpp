#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int P = 998244353;

void solve()
{
    int n,k;
    cin>>n>>k;
    vector<int>s(n + 1);
    for(int i = 1;i <= n;i++){
        cin>>s[i]; 
    }
    vector<int>dp(n + 1);// \sum [0,i] = 0 ->cnt
    dp[0] = 1;
    int sum = 1;
    for(int i = 1;i <= n;i++){
        //v[i] = 0
        dp[i] = (dp[i] + dp[i - 1]) % P; 
        //v[i] = k, v[i + 1] = 1
        if(s[i] != s[i - 1]){
            for(int j = i - 1;j >= 1;j--){
                if(s[j] == s[i - 1]){
                    dp[i] = (dp[i] + dp[j - 1]) % P;
                }
                else{
                    break;
                }
            }
        }
    }
    // for(int i = 0 ;i <= n;i++){
    //     cerr<<dp[i]<<" ";
    // }
    // cerr<<endl;
    cout<<dp[n]<<endl;
    return;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt = 1;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}
