#include<bits/stdc++.h>
using ll = long long;
using i64 = long long;

using namespace std;

void solve()
{
    int n;cin>>n;
    map<int,int>a,b;
    string s,t;
    if(n>1)cin>>s>>t;
    int lst = -1;
    for(int i=0;i<s.size();i++){
        if(s[i] =='1'){
            a[i-lst]++;
            lst = i;
        }
    }
    a[n-1-lst]++;
    lst = -1;
    for(int i=0;i<t.size();i++){
        if(t[i] == '1'){
            b[i-lst]++;
            lst = i;
        }
    }
    b[n-1-lst]++;
    ll res = 0;
    for(auto [x,y]:a){
        for(auto [u,v]:b){
            if(y%2 && v % 2) res ^= 1ll * x * u;
        }
    }
    cout<<res<<'\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    while(tt--){
        solve();
    }
    return 0;
}