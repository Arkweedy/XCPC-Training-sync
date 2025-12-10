#include<bits/stdc++.h>
using ll = long long;
using namespace std;

constexpr int N = 1e5;

void solve()
{
    int n,k;cin>>n>>k;
    vector<int>a(n),b(n);
    for(int i=0;i<n;i++)cin>>a[i];
    for(int i=0;i<n;i++)cin>>b[i];

    sort(a.begin(),a.end(),greater<int>());
    sort(b.begin(),b.end(),greater<int>());

    vector<vector<ll>>dp(k+1,vector<ll>(k+1));

    ll inf = 1e18;

    for(int i=0;i<2*n;i++){
        vector<vector<ll>>ndp(k+1,vector<ll>(k+1,inf));
        int cnt = 2 * n - i -1,A = (cnt+1)/2,B = (cnt)/2;
        if(i&1){
            // A
            for(int i=0;i<=k;i++){
                for(int j=0;j<=k;j++){
                    if(i > A || j > B)continue;
                    int x = i + B - j;
                    int y = j + A - i;
                    if(x < n && i + 1 <= k){
                        ndp[i][j] = max(ndp[i][j],dp[i+1][j] + a[x]);
                    }
                    if(y < n){
                        ndp[i][j] = max(ndp[i][j],dp[i][j]);
                    }
                }
            }
        }else{
            // B
            for(int i=0;i<=k;i++){
                for(int j=0;j<=k;j++){
                    if(i > A || j > B)continue;
                    int x = i + B - j;
                    int y = j + A - i;
                    if(x < n){
                        ndp[i][j] = min(ndp[i][j],dp[i][j]);
                    }
                    if(y < n && j + 1 <= k){
                        ndp[i][j] = min(ndp[i][j],dp[i][j+1]-b[y]);
                    }
                }
            }
        }

        inf *= -1;
        dp = move(ndp);
    }

    cout<<dp[0][0]<<'\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    while (tt--)
    {
        solve();
    }
    return 0;    
}
