#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.31 16:16:31

void solve()
{
    int n;cin>>n;
    vector<int>p(n+1),q(n+1);
    for(int i=1;i<=n;i++){
        cin>>p[i];
        q[p[i]] = i;
    }
    for(int i=1;i<n;i++){
        if(abs(q[i]-q[i+1]) > 2){
            cout<<"No\n";
            return;
        }
    }
    cout<<"Yes\n";
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