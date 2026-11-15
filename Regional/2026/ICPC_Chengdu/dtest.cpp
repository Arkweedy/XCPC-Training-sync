#include<bits/stdc++.h>

using ll = long long;
using i64 = long long;
 
using namespace std;
int K=3;
int dp[100];
void solve()
{
    for(int i=1;i<100;i++){

        int j=i+K;
        dp[i]=1;
        if(j-4<=0) dp[i]=0;
        for(int j=1;j<=4;j<<=1){
            if(i-j<0) continue;
            if(dp[i-j]==0) dp[i]=0;
        }
        cout<<i<<' '<<dp[i]<<endl;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}