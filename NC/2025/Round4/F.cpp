#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    ll n,k,c;
    cin>>n>>k>>c;
    vector<ll>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    ll ans = 0;
    priority_queue<ll>pq1,pq2;
    for(int i = 0;i < k;i++){
        pq1.push(- a[i] - (k - 1 - i) * c);
        ans += a[i];
    }
    for(int i = k;i < n;i++){
        pq2.push(a[i] - (i - k + 1) * c);
    }
    
    while(!pq1.empty() && !pq2.empty()){
        if(pq1.top() + pq2.top() <= 0){
            break;
        }
        else{
            ans += pq1.top() + pq2.top();
            pq1.pop(),pq2.pop();
        }
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