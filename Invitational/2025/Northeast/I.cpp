#include<bits/stdc++.h>
#define N 200009
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;
int n,s,t,a[N];
using namespace std;


void solve()
{
    cin>>n>>s>>t;
    for(int i=1;i<=n;i++) cin>>a[i];
    if(s>t) swap(s,t);
    int ans;
    if(s<=n&&t>n)
    {
        if(a[s]==t) ans=0;
        else ans=1;
    }
    else{
        if(s==t||n>2) ans=1;
        else ans=0;
    }
    if(ans) cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
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