#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;
constexpr int N =2e5+10;

//Create time: 2026.01.20 10:35:36
int n,bb;
ll a[N];
int b[N<<1];
int deal(int p)
{
    for(int i=1;i<=n;i++)
    {
        if(a[i]>>p&1) b[i]=1;
        else b[i]=0;
        b[i+n]=b[i];
    }
    int sum=0;
    for(int i=1;i<=n;i++) sum+=b[i];
    if(sum==0) return 1;
    if(sum==n) return n;
    int ans=n;
    int st=1;
    while(b[st]) st++;
    for(int i=st;i<st+n;i++)
    {
        if(!b[i]) continue;
        int r=i;
        while(b[r]) r++;
        r--;
        ans=min(ans,r-i+1);
        i=r;
    }
    return ans;
}
void solve()
{
    cin>>n>>bb;
    for(int i=1;i<=n;i++) cin>>a[i];
    int ans=n;
    for(int i=0;i<bb;i++) ans=min(ans,deal(i));
    cout<<ans<<'\n';
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
//    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}