#include<bits/stdc++.h>

using ll = long long;
using uint =  unsigned int;

using namespace std;

constexpr int N = 1e5 + 10,mod = 998244353;

int lowbit(int x)
{
    return x & -x;
}

ll qmi(ll a,ll k){
    ll res = 1;
    while(k){
        if(k&1)res=res*a%mod;
        k>>=1;
        a=a*a%mod;
    }
    return res;
}

array<int,4> operator+(const array<int,4>&a, const array<int,4>&b)
{
    int xl = max(a[0], b[0]), xr = min(a[2], b[2]);
    int yl = max(a[1], b[1]), yr = min(a[3], b[3]);
    if(xl >= xr || yl >= yr)return {-1,-1,-1,-1};
    else return {xl,yl,xr,yr};
}

void solve()
{
    int n;
    cin>>n;
    vector<array<int,4>>a(n + 1);
    int h, w;
    cin>>h>>w;
    a[n] = {0,0,h,w};
    for(int i = 0;i < n;i++){
        cin>>a[i][0]>>a[i][1]>>a[i][2]>>a[i][3];
    }

    auto merge = [&](const array<int,4>&a, const array<int,4>&b)->array<int,4>
    {
        int xl = max(a[0], b[0]), xr = min(a[2], b[2]);
        int yl = max(a[1], b[1]), yr = min(a[3], b[3]);
        if(xl >= xr || yl >= yr)return {-1,-1,-1,-1};
        else return {xl,yl,xr,yr};
    };

    int len = 1 << n + 1;
    vector<array<int,4>>in(len);
    vector<ll>sqr(len);
    vector<ll>ss(len);

    constexpr int N = 1e9;
    in[0] = {0,0,N,N};
    sqr[0] = 0;

    for(int i = 1;i < (1 << n + 1);i++){
        in[i] = in[i - lowbit(i)] +  a[__lg(lowbit(i))];
        sqr[i] = 1ll * (in[i][2] - in[i][0]) * (in[i][3] - in[i][1]);
        ss[i] = (popcount(uint(i)) % 2 == 1 ? 1 : -1) * sqr[i];
    }

    for(int j = 0;j < n + 1;j++){
        for(int i = 0;i < len;i++){
            if(i >> j & 1){
                ss[i] += ss[i ^ (1 << j)];
            }
        }
    }

    // for(int i = 0;i < len;i++){
    //     cerr<<ss[i]<<" ";
    // }
    // cerr<<endl;

    int m = 1 << n;
    vector<int>ok(m);

    for(int i = 0;i < m;i++){
        int x = i + m;
        if(ss[i] == ss[x]){
            ok[i] = 1;
        }
    }
    
    if(ok[m-1] == 0){
        cout<<-1<<'\n';
        return;
    }

   

    vector<int>dp(m);
    for(int i = m-1;i>=0;i--){
        if(ok[i])continue;
        ll sum = 0,c = 0;
        for(int j=0;j<n;j++){
            if(i>>j&1){
                c++;
                continue;
            }
            sum = (sum + dp[i^(1<<j)])%mod;
        }
        dp[i] = (n+sum)%mod * qmi(n-c,mod-2)%mod;

    }

    cout<<dp[0]<<'\n';



}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int tt = 1;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}