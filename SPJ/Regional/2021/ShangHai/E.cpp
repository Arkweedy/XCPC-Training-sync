#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,k;cin>>n>>k;
    vector<int>a(n);
    for(int i=0;i<n;i++)cin>>a[i];
    sort(a.begin(),a.end());
    vector<int>b(1,-k);
    int res = 0;
    for(auto x:a){
        if(x >= b.back() + k){
            res ++;
            b.push_back(x);
        }
    }
    cout<<res<<'\n';
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