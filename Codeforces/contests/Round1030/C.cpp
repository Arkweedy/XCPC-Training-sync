#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    ll n,k;
    cin>>n>>k;
    vector<ll>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    vector<array<int,62>>p(n);
    ll buty = 0;
    priority_queue<ll,vector<ll>,greater<ll>>pq;
    for(int i = 0;i < n;i++){
        int base = __popcount(a[i]);
        buty += base;
        for(int j = 0;j < 62;j++){
            if((a[i] >> j & 1) == 0){
                pq.push(1ll << j);
                // need += 1ll << j;
                // more++;
                // p[i][base + more] = need;
            }
        }
    }
    while(!pq.empty() && k >= pq.top()){
        k -= pq.top();
        buty++;
        pq.pop();
    }
    cout<<buty<<endl;
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