#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,v;
    cin>>n>>v;
    vector<int>h(n),s(n),d(n);
    for(int i = 0; i < n;i++){
        cin>>h[i]>>s[i]>>d[i];
    }
    ll ans = 0;
    constexpr ll inf = 1e15;
    for(int cap = 1;cap <= v;cap++){
        vector<ll>dp(cap + 1,-inf);
        vector<priority_queue<ll>>chs(cap + 1);
        int emp = v - cap;
        for(int i = 0;i < n;i++){
            if(s[i] <= cap)
                chs[s[i]].push(h[i] - 1ll * emp * d[i]);
        }
        dp[0] = 0;
        for(int i = 1;i <= cap;i++){//size
            for(int t = 0;t < cap / i;t++){//rounds
                if(chs[i].empty())break;
                ll val = chs[i].top();
                chs[i].pop();
                for(int j = cap;j >= i;j--){
                    dp[j] = max(dp[j], dp[j - i] + val);
                }
            }
        }
        ans = max(ans, dp[cap]);
    }
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