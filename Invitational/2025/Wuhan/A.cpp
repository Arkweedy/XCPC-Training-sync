#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.10.31 14:54:40

void solve()
{
    int n,q;
    cin>>n>>q;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    constexpr int inf = 1e9;
    vector<int>l(n,0),r(n, 1e9);
    for(int i = 0;i < q;i++){
        int p,x,y;
        cin>>p>>x>>y;
        p--;
        l[p] = max(l[p],x);
        r[p] = min(r[p],y);
    }
    ll ans = 0;
    for(int i = 0;i < n;i++){
        if(l[i] > r[i]){
            cout<<-1<<endl;
            return;
        }
        else if(a[i] < l[i]){
            ans += l[i] - a[i];
        }
        else if(a[i] > r[i]){
            ans += a[i] - r[i];
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
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}