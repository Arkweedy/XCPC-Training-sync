#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

const int N = 1e6 + 10;

ll n,a[N],b[N],c[N],cnt[N];

bool check(ll x){
    ll sum = 0;
    for(int i=1;i<=n;i++){
        cnt [i] = x/c[i];
        sum += cnt[i];
    }
    ll ans = 0;
    for(int i=1;i<=n;i++){
        if(sum - cnt[a[i]] < b[i])return 0;
        ans += b[i];
    }
    return sum >= ans;
}

void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=n;i++)cin>>b[i];
    for(int i=1;i<=n;i++)cin>>c[i];

    ll l = 1,r = 1e12;
    while(l<r){
        ll mid = l+r>>1;
        if(check(mid))r=mid;
        else l=mid+1;
    }
    cout<<l<<'\n';
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}