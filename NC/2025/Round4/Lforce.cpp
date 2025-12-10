#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,q;
    cin>>n>>q;
    vector<int>a(n + 1);
    for(int i = 1;i <= n;i++){
        cin>>a[i];
    }

    while(q--){
        int x,y;
        cin>>x>>y;
        int z = x;
        y = n + 1 - y;
        int p = upper_bound(a.begin(),a.end(),x)-a.begin();
        for(int i = p;i <= y;i++){
            x = (a[i] + x + 1) / 2;
        }
        cout<<x - z<<endl;
    }
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