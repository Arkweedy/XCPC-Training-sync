#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n;
    string s;
    cin>>n>>s;
    s = s + s[0];
    auto get = [&](string &s)->int
    {
        vector<array<int,2>>dp(n + 1,{0,0});
        for(int i = 1;i <= n;i++){
            if(i % 2 == 0){//dp[i][0] -> 0
                if(s[i] == '0'){
                    dp[i][0] = dp[i - 1][0];//0->0
                    dp[i][1] = dp[i - 1][1] + 1;//0->1
                    if(i >= 2 && s[i - 1] == '1')dp[i][1] = min(dp[i][1],dp[i - 2][1] + 1);//10->01
                    
                }
                else{
                    dp[i][0] = dp[i - 1][0] + 1;//1->0
                    dp[i][1] = dp[i - 1][1]; 
                    if(i >= 2 && s[i - 1] == '0')dp[i][0] = min(dp[i][0],dp[i - 2][0] + 1);
                    
                }
            }
            else{// dp[i][0] -> 1
                if(s[i] == '0'){
                    dp[i][1] = dp[i - 1][1];
                    dp[i][0] = dp[i - 1][0] + 1;
                    if(i >= 2 && s[i - 1] == '1')dp[i][0] = min(dp[i][0],dp[i - 2][0] + 1);
                }
                else{
                    dp[i][1] = dp[i - 1][1] + 1;
                    dp[i][0] = dp[i - 1][0];
                    if(i >= 2 && s[i - 1] == '0')dp[i][1] = min(dp[i][1],dp[i - 2][1] + 1);
                }
            }
        }
        int ans = min(dp[n][0],dp[n][1]);
        return ans;
    };
    int ans = get(s);
    s.pop_back();
    s = s[n - 1] + s;
    ans = min(ans,get(s));
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