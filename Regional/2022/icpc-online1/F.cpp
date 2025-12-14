#include<bits/stdc++.h>
#define N 200009
#define ls p<<1
#define rs p<<1|1
#define lowbit(x) ((x)&-(x))
using namespace std;
using ll =long long ;
const ll INF =1e18;
const int mod=1e9+7;

/*
f(k-1,x) sqrt(n) * O(f)

O(30*30)

g(i,x) = g(i-1,x/2...)

*/

unordered_map<int,int> memo[40];

//const int N = 1e5+10;

int c[40][N];


int g(int i,int x){
    if((1<<i)>x)return 0;
    if(x < N)return c[i][x];
    if(i == 0)return 0;
    if(memo[i].count(x))return memo[i][x];
    int res = 0;
    for(int l=2,r;l<=x;l=r+1){
        r = x/(x/l);
        res = (res + 1ll * g(i-1,x/l) * (r-l+1))%mod;
    }
    return memo[i][x] = res;
}

int n,k;

ll qmi(ll a,ll k){
    ll res = 1;
    while(k){
        if(k&1)res = res * a%mod;
        k>>=1;
        a=a*a%mod;
    }
    return res;
}

ll infact[100],fact[100],inv[100];

ll binom(int a,int b){
    if(b<0||a<b)return 0;
    ll res = infact[b];
    while(b){
        res = res * a %mod;
        a--,b--;
    }
    return res;
}

int f(int x){
    int res = 0;
    /*
    i 
    i + 1
    x_1 +... + x_(i+1) = (k - 1) - i

    c(k-1,i)
    */
    ll ans = 1;
    for(int i=0;i<min(30,k);i++){
        res =( res + ans * g(i,x))%mod;
        ans = ans * (k-1-i)%mod * inv[i+1]%mod; 
    }
    return res;
}


void solve()
{
    for(int i=1;i<100;i++)inv[i] = qmi(i,mod-2);
    c[0][1] = 1;
    for(int i=1;i<30;i++){
        for(int j=2;j<N;j++){
            for(int k=j;k<N;k+=j){
                c[i][k] = (c[i][k] + c[i-1][k/j]);
                if(c[i][k]>=mod)c[i][k] -= mod;
            }
        }
    }
    for(int i=0;i<30;i++){
        for(int j=1;j<N;j++){
            c[i][j] = (c[i][j] + c[i][j-1]);
            if(c[i][j]>=mod)c[i][j] -= mod;
        }
    }
    
    cin>>n>>k;
    ll res = 0;
    for(int l=1,r;l<=n;l=r+1){
        r = n/(n/l);
        ll ans = f(n/l);
        res = (res + ans*(r-l+1))%mod;
    }
    cout<<res<<'\n';
}
/*
996238996
*/

int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    int tt=1;
    while(tt--) solve();
    return 0;
}

