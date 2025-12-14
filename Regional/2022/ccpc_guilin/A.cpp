#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e5 + 10;

void solve()
{
    int n;cin>>n;
    string s;cin>>s;
    auto t = s;
    for(int i=0;i<n;i++){
        bool ok = 1;
        if(i+1<n && s[i+1] == 'L')ok = 0;
        if(i && s[i-1] == 'L')ok = 0;
        if(s[i] == 'L')ok = 0;
        if(ok)t[i] = 'C';
    }
    cout<<t<<'\n';
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