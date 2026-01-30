#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.29 11:03:07

int n,a[100009];
void solve()
{
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);
    if(a[n]==0)
    {
        cout<<"Puss in Boots";
        return ;
    }
    ll sum=0;
    for(int i=1;i<n;i++) sum+=a[i];
    if(sum>=n) cout<<"Puss in Boots";
    else cout<<"Donkey";

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