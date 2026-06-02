#include<bits/stdc++.h>
constexpr int N =1000009;
using ll = long long;
using i64 = long long;
using namespace std;
short K =170;

int ans[N];
unordered_map<ll,unsigned char > mp;
int a[1000],can[1000];
int cnt=0;
unsigned char  dfs(ll p)
{
    //cnt++;
    if(cnt>N) return 0;
    if(p<N) return ans[p];
    int g=mp[p];
    if(g) return g;
    int ans=1000;
    for(int i=0;i<=20;i++){
        ll g=p-i;
        for(int j=2;j<=20;j++)
            if(can[j]&&g%j==0&&j>1) ans=min(ans,i+j+2+dfs(g/j));
    }
    mp[p]=ans;
    return ans;
}

void solve()
{
    
    ll n;cin>>n;
    ans[0]=0;
    for(int i=1;i<N;i++) ans[i]=1000;
    int ma=0;
    for(int i=0;i<N;i++){
        for(int j=2;j<=200;j++) 
            if(i*j<N) ans[i*j]=min(ans[i*j],j+2+ans[i]);
        if(i+1<N) ans[i+1]=min(ans[i+1],1+ans[i]);
        ma=max(ma,ans[i]);
    }
    // for(int i=N-100;i<N;i++) cerr<<ans[i]<<endl;
    // cout<<ma<<endl;
    cout<<(int)dfs(n)<<'\n';
    //cout<<cnt;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    a[1]=3;
    for(int i=2;i<=200;i++){
        int err=0;
        int s=i+2;
        a[i]=i+2;
        for(int j=1;j<=i;j++)
            if(i%j==0) 
            {
                if(a[j]+a[i/j]<=s) err=1;
                a[i]=min(a[j]+a[i/j],a[i]);
            }
        if(!err) can[i]=1;
        
    //    cerr<<i<<' '<<a[i]<<endl;

    }
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}