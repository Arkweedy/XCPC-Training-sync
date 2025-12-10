#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using i128 = __int128;
using namespace std;

const int N  = 2e5  + 10;

int n;
ll a[N];
ll b[N];

ll check(ll k){
    for(int i=1;i<=n;i++){
        b[i] = a[i] - i * k;
    }
    sort(b+1,b+n+1);
    int t = (n+1)/2;
    ll res = 0;
    for(int i=1;i<=n;i++){
        if(b[i] >= b[t])res += b[i] - b[t];
        else res += b[t] - b[i];
    }
    return res;
}

void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a[i];
    ll l =-2e13,r =2e13;
    while(l<r){
        ll mid = l + (r-l)/2;
        if(check(mid) <= check(mid+1))r = mid;
        else l = mid+1;
    }
    cout<<(ll)check(l)<<'\n';
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