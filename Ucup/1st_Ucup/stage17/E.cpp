#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int N =1e6+10;
//Create time: 2026.01.31 16:04:30
int l[N],r[N],p;
string s;
int n;
void solve()
{
    cin>>s;
    n=s.length();
    s=' '+s;
    int p=0;
    for(int i=1;i<=n;i++)
    {
        l[i]=p;
        if(s[i]=='p') p=i;
    }    
    p=n+1;
    for(int i=n;i;i--)
    {
        r[i]=p;
        if(s[i]=='p') p=i;
    }
    ll ans=0;
    for(int i=1;i<=n;i++)
        if(s[i]!='c')
        {
            int lnum=i-l[i]-1,rnum=r[i]-i-1;
            ans+=min(lnum/2,rnum);
        }
    cout<<ans<<'\n';
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