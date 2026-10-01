#include<bits/stdc++.h>
#define N 1000009
using i64 = long long;
using ll = long long;
using ull = unsigned long long;

using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
map<ull,ull> mp;
ull mix(ull x)
{
    if(mp.count(x)) return mp[x];
    mp[x]=rng();
    return mp[x];
    
}

ull a[N],b[N],c[N];
ull s[N],ss[N],sss[N];
void solve()
{
    int n;
    cin>>n;
    mp.clear();
    int ans=1;
    //for(int i=1;i<=6;i++) cout<<mix(i)<<endl;
    for(int i=1;i<=n;i++){
        cin>>a[i];s[i]=mix(a[i]);s[i]^=s[i-1];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];ss[i]=mix(b[i]) ;ss[i]^=ss[i-1];
    }
    for(int i=1;i<=n;i++){
        cin>>c[i];sss[i]=mix(c[i]);sss[i]^=sss[i-1];
    }
    //for(int i=1;i<=n;i++) cout<<a[i]<<b[i]<<endl;
    //cout<<s[2]<<' '<<ss[2]<<endl;
    for(int i=1;i<n;i++){
        int g=(s[i]==ss[i])+(ss[i]==sss[i])+(sss[i]==s[i]);
        if(g) ans++;
    }
    cout<<ans<<'\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}

