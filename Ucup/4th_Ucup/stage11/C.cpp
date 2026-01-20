#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;
constexpr int mod=1e9+7;
constexpr int N =2e5+10;
//Create time: 2026.01.20 10:35:36
struct LB{
    const int BASE=60;
    int cnt=0;
    vector<ll> d;
    LB(){
        d.assign(BASE,0);
        cnt=0;
    }
    bool insert(ll val){
        for(int i=BASE-1;i>=0;i--){
            if(val&(1ll<<i)) {
                if(!d[i]) {
                    cnt++;
                    d[i]=val;
                    return 1;
                }
                val^=d[i];
            }
        }
        return 0;
    }
}A,B;
int nn;
ll a;
int p[N];
vector<ll> AA;
int m=0,k=0;
int cal()
{
    int ans=0;
    for(auto x : AA)
    {
        LB C = B;
        //ans++;
        if(C.insert(x))ans++;
    }
    return ans;
}
void solve()
{
    p[0]=1;
    for(int i=1;i<N;i++) p[i]=1ll*2*p[i-1]%mod;
    cin>>nn;
    for(int n=1;n<=nn;n++)
    {
        cin>>a;
        int ch=0;
        if(A.insert(a))
        {
            ch=1;m++;AA.push_back(a);
        }
        else if(B.insert(a))
        {
            ch=1;
        }
        if(ch)  k=cal();
        ll ans=0;
        if(n>m) ans=(ans+1ll*(n-m)*p[n-m-1])%mod;
        ans=(ans+1ll*k*p[n-m])%mod;
        if(n>m) ans=(ans+1ll*(m-k)*p[n-m-1])%mod;
    //    cerr<<n<<' '<<m<<' '<<k<<endl;
        ans=(p[n]-ans)%mod;
        ans=(ans%mod+mod)%mod;
        cout<<ans<<'\n';
        
    }
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

