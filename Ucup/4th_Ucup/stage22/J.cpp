#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//J.cpp Create time : 2026.04.07 16:17

using ll = long long;
const int N = 1e8 + 10,M=1e4;

int h[N],ne[N],tot,mod,n;
short e[N];

void add(int x,int y){
    tot++;
    e[tot] = y;
    ne[tot] = h[x];
    h[x] = tot;
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

void solve()
{
    cin>>n>>mod;
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            add(i*j,i);
        }
    }
    vector<ll>inv(n+1);
    vector<int>c(n+1);
    for(int i=1;i<=n;i++)inv[i] = qmi(i,mod-2);
    int cnt = 0,inf = 1e8;
    for(int i=1;i<=n;i++){
        c[i] = (n - 1) / i;
        c[i] -= n - i;
        if(c[i] <= 0)cnt++;
    }
    
    ll last = 0,val = 1,res = 0;
    for(int i=n;i<=n * n;i++){
        for(int j=h[i];j;j=ne[j]){
            int x = e[j], y = i / x;
            c[x]++;
            if(c[x] == 1){
                cnt--;
            }else if(c[x] > 0){
                val = val * inv[c[x]-1] % mod * c[x] % mod;
            }
            if(y!=x){
                swap(x,y);
                c[x]++;
                if(c[x] == 1){
                    cnt--;
                }else if(c[x] > 0){
                    val = val * inv[c[x]-1] % mod * c[x] % mod;
                }
            }
        }
        if(cnt)last = 0;
        else{
            res = ( res + (val - last + mod) % mod * i % mod ) % mod;
            last = val;
        }
    }
    cout<<res<<'\n';
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    while(tt--){
        solve();
    }
    return 0;
}