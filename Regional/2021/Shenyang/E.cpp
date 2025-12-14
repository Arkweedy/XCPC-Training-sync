#include<bits/stdc++.h>

using ll = long long;

using namespace std;

constexpr int N = 1e5 + 10;
string s,ss="edgnb";
void solve()
{
    int ans=0;
    cin>>s;
    for(int i=0;i+4<s.length();i++)
    {
    //    cout<<i<<endl;
        string sss;
        for(int j=i;j<=i+4;j++) sss+=s[j];
    //    cout<<sss<<ss;
        if(sss==ss) ans++;
    }
    cout<<ans;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin>>tt;
    while(tt--){
        solve();
    }
}