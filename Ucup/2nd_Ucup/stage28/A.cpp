#include<bits/stdc++.h>

using namespace std;

using ll = long long;


constexpr ll INF = 1e18;
constexpr int mod = 1e9 + 7;
constexpr int N = 1e6 + 10;

int n;
ll a[N],b[N];
void solve()
{
    cin>>n;
    
    for(int i=1;i<=n;i++){
        cin>>a[i];
        b[i]  = a[i];
    }
    
    ll res =  1e18;
    for(int s=0;s<=100;s++){
        ll l = 0,r = 1e18;
        ll ans = s;
        b[1] = s + a[1];
        for(int i=1;i<=n;i++){
            if(b[i]<l)b[i] = l;
            /*
            l  a[i] - l
            */
            if(b[i]-l > r)l += b[i] -l -r;
            r = b[i] - l;
            //cout<<l<<' '<<r<<endl;
            ans += b[i];
        }
        res = min(res,ans);
    }
    cout<<res<<'\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}