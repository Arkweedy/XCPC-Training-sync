#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,m;
    cin>>n>>m;
    vector<int>h(n + 2);
    for(int i = 0;i < m;i++){
        int l,r,v;
        cin>>l>>r>>v;
        h[l] += v;
        h[r + 1] -= v;
    }
    for(int i = 1;i <= n;i++){
        h[i] += h[i - 1];
    }
    for(int i = 1;i <= n;i++){
        cout<<h[i]<<" ";
    }
    cout<<endl;
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