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
    vector<int>q(n),r(n),s(n);
    for(int i = 0;i < n;i++){
        cin>>q[i]>>r[i]>>s[i];
    }
    ll sq = 0,sr = 0,ss = 0;
    for(int i = 0;i < n;i++){
        sq[i] += q[i];
        sr[i] += r[i];
        ss[i] += s[i];
    }
    
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