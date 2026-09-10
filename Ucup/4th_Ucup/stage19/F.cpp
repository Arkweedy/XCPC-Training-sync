#include<bits/stdc++.h>
#define NN 1000009
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.09.10 21:00:34

constexpr int P = 998244353;
int power(int a, int p)
{
    int res = 1;
    while(p){
        if(p & 1)res = 1ll * res * a % P;
        a = 1ll * a * a % P;
        p >>= 1;
    }
    return res;
}

int inv(int a)
{
    return power(a, P - 2);
}
vector<int> ve[NN],dp[NN];
int vis[NN];
void solve()
{
    int ans=0;
    int n, l;
    cin >> l >> n;
    const int N = l * 2 + 1;
    vector<int>fac(N + 1), invfac(N + 1);
    fac[0] = 1;
    for(int i = 1;i <= N;i++){
        fac[i] = 1ll * fac[i - 1] * i % P;
    }
    invfac[N] = inv(fac[N]);
    for(int i = N - 1;i >= 0;i--){
        invfac[i] = 1ll * invfac[i + 1] * (i + 1) % P;
    }

    auto binom = [&](int n, int m)->int
    {
        if(n < 0 || m < 0 || n < m)return 0;
        return 1ll * fac[n] * invfac[m] % P * invfac[n - m] % P;
    };

    auto f = [&](int n, int t, int m)->int // n beats to t seg, max leq m
    {
    //    cerr<<n<<' '<<t<<' '<<m<<endl;
        //return 0;
        //return 0;
        int res = 0;
        if(n < t)return 0;
        n -= t;
        for(int i = 0;i <= min(n / m, t);i++){
            int x = ((i % 2 == 0 ? 1 : -1) * binom(t, i) + P) % P;
            res = (res + 1ll * x * binom(t + n - i * m - 1, n - i * m)) % P;
        }
    //    cerr << "ok" << endl;
        return res;
    };
    for(int i=1;i<=l;i++) {
        if(l%i) continue;
        int t=l/i;
        if(n%t==0) {
            vis[i]=1;
        }
    }
    for(int i=1;i<=l;i++){
        if(vis[i]==0) continue;
        for(int j=2*i;j<=l;j+=i)
            if(vis[j]) ve[j].push_back(i);
    }
    //cout<<f(2,2,2)<<endl;
    //return ;
    for(int i=1;i<=l;i++)
        if(vis[i]){
        //    cout<<i<<endl;
            int t=l/i;
            int lll=n/t;
            dp[i].push_back(0);
            dp[i].resize(i+1);
        //    if(i==2) cout<<i<<lll<<endl;
            for(int j=1;j<=i;j++) dp[i][j]=f(i,lll,j);
            //if(i==2) cout<<dp[i][2]<<' '<<dp[i][1]<<' '<<dp[i][0]<<endl;
            for(int j=i;j;j--) dp[i][j]=(dp[i][j]+P-dp[i][j-1])%P;
            for(auto p:ve[i]){
                for(int j=0;j<dp[p].size();j++){
                    dp[i][j]=(dp[i][j]+P-dp[p][j])%P;
                }
            }
            for(int j=1;j<=i;j++) ans=(ans+1ll*j*i%P*dp[i][j]%P*inv(lll)%P)%P;
        }

//    cout<<dp[1][1]<<' '<<dp[2][1]<<' '<<dp[2][2]<<endl;
        //cout<<endl;
    //return ;
    ans=1ll*ans*fac[n]%P*fac[l-n]%P*invfac[l]%P;
    ans=(ans%P+P)%P;
    cout<<ans;
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