#include<bits/stdc++.h>

using namespace std;

using ll = long long;

constexpr ll INF = 1e18;
constexpr int mod = 998244353;
constexpr int N = 2e5 + 10;

int cnt[N],n,a[N];
vector<int>d[N];

ll qmi(ll a,ll k){
    ll res = 1;
    while(k){
        if(k&1)res=res*a%mod;
        k>>=1;
        a=a*a%mod;
    }
    
    return res;
}

int p[30];

bool insert(int x){
    for(int i=19;i>=0;i--){
        if(x>>i&1){
            if(!p[i]){
                p[i] = x;
                return 1;
            }
            x ^= p[i];
        }
    }
    return 0;
}

void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++)cnt[i] = 0,d[i].clear();
    memset(p,0,sizeof p);
    for(int i=1;i<=n;i++){
        cin>>a[i];
        cnt[a[i]]++;
    }
    int res = 0;
    for(int i=1;i<=n;i++){
        for(int j=i*2;j<=n;j+=i)d[j].push_back(i);
    }
    for(int i=1;i<=n;i++){
        if(cnt[i] == 0)continue;
        memset(p,0,sizeof p);
        int sum = 0,r = 0;
        for(auto j:d[i]){
            sum += cnt[j];
            if(cnt[j])r += insert(j);
        }
        
//        cout<<i<<"#\n";
//        cout<<sum<<' '<<r<<endl;
//        cout<<qmi(2,cnt[i]-1) * qmi(2,sum-r)<<endl;
        res = (res + 1ll * qmi(2,cnt[i]-1) * qmi(2,sum-r)%mod)%mod;
    }
    int r = 0;
    memset(p,0,sizeof p);
    for(int i=1;i<=n;i++){
        r += insert(a[i]);
        //cout<<r<<' '<<a[i]<<endl;
    }
    //cout<<qmi(2,n-r)<<' '<<res<<endl;
    res = (res + qmi(2,n-r))%mod;
    cout<<(res-1+mod)%mod<<'\n';
}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
