#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.02 13:47:01
int n;
int a,b;
void solve()
{
    cin>>n;
    a=b=n;
    for(int k=1;k<=3;k++)
    {
        int cnt0=0,cnt1=0;
        for(int i=1;i<=n;i++)
        {
            char c;cin>>c;
            if(c=='0') cnt0++;
            else cnt1++;
        }
        a=min(a,cnt0),b=min(b,cnt1);
    }
    cout<<max(a,b)<<'\n';
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