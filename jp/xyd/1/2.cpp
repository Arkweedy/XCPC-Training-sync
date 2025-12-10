#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n;
    cin>>n;
    priority_queue<ll,vector<ll>,greater<ll>>pq;
    for(int i = 0;i < n;i++){
        ll x;
        cin>>x;
        pq.push(x);
    }
    ll ans = 0;
    while(pq.size() >= 2){
        ll a = pq.top();pq.pop();
        ll b = pq.top();pq.pop();
        ans += a + b;
        pq.push(a + b);
    }
    cout<<ans<<endl;
    return;
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