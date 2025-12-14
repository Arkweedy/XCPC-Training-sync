#include<bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int N = 1e5 + 10,mod = 998244353;

struct mat{
    ll c[3][3];
    mat(){
        memset(c,0,sizeof c);
    }
};

mat operator * (mat A,mat B){
    mat C;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            for(int k=0;k<3;k++){
                C.c[i][j] = (C.c[i][j] + A.c[i][k] * B.c[k][j]) % mod;
            }
        }
    }
    return C;
}

ll power(ll a, ll p)
{
    ll res = 1;
    while(p){
        if(p & 1)res = res * a % mod;
        a = a * a % mod;
        p >>= 1;
    }
    return res;
}

mat qmi(mat A,ll k){
    mat res;
    for(int i=0;i<3;i++)res.c[i][i] = 1;
    while(k){
        if(k&1)res = res * A;
        k>>=1;
        A = A * A;
    }
    return res;
}

void solve()
{
    ll n,m;cin>>n>>m;
    ll a = power(2,m);
    ll b = (a-1+mod)%mod;
    if(n==1)cout<<1<<'\n';
    else if(n==2)cout<<0<<'\n';
    else if(m==0)cout<<0<<'\n';
    else{
        mat A;
        A.c[0][1] = (-b+mod)%mod;
        A.c[0][2] = a;
        A.c[1][0] = 1;
        A.c[2][2] = b;
        mat B = qmi(A,n-2);
        ll res = (B.c[0][1] + b * B.c[0][2])%mod;
        cout<<res<<'\n';
    }
}


int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int tt = 1;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}
