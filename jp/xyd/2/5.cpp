#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n;
    ll s;
    cin>>n>>s;
    vector<ll>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    int l = 0, r = 0;
    ll sum = 0;
    int inf = 1145141919;
    int ans = inf;
    while(r != n){
        sum += a[r++];
        while(sum - a[l] >= s && l < r){
            sum -= a[l++];
        }
        
        if(sum >= s){
            ans = min(ans,max(1,r - l));
        }
    }
    cout<<(ans == inf ? 0 : ans)<<endl;
    return;
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