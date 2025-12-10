#include<bits/stdc++.h>

using ll = long long;

using namespace std;

constexpr int N = 1e5 + 10,mod = 1e9+7;

ll qmi(ll a,ll k){
    ll res = 1;
    while(k){
        if(k&1)res=res*a%mod;
        k>>=1;
        a=a*a%mod;
    }
    return res;
}

void solve()
{
    int n,m;cin>>n>>m;
    int cnt = 0;
    bool flg = 0;
    vector<int>a(n);
    for(int i=0;i<n;i++){
        cin>>a[i];
        if(a[i] > 1 && a[i] < n)flg = 1;
        if(a[i] == -1)cnt++;
    }

    if(flg){
        cout<<qmi(m,cnt)<<'\n';
        return;
    }

    ll res = qmi(m,cnt);

    ll s = 1;
    if(m>=n)s += m - n + 1;

    res = (res - qmi(s,cnt) + mod)%mod;

    ll dp[2][2] = {0};// pre 相邻 1 first

    dp[1][0] = 1;

    ll c[] = {s-1 , 1};


    for(auto x:a){
        ll ndp[2][2] = {0};
        vector<int>v;
        if(x == 1){
            v = {1};
        }else if(x >= n){
            v = {0};
        }else{
            v = {0,1};
        }
        for(auto y:v){
            for(int i=0;i<2;i++){
                for(int j=0;j<2;j++){
                    int st = j | (i&y);
                    ll ans = x == -1 ? c[y] : 1;
                    ndp[y][st] = (ndp[y][st] + dp[i][j] * ans) % mod;
                }
            }
        }

        memcpy(dp,ndp,sizeof dp);
    }

    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            if(i|j)res = (res + dp[i][j])%mod;
        }
    }

    cout<<(res+mod)%mod<<'\n';

}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    while(tt--){
        solve();
    }
    return 0;
}