#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.20 10:35:36
int a[200];
void solve()
{
    int k;
    int g=100,n=199;
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    for(int i=1;i<=g;i++) a[i]=1;
    shuffle(a+1,a+n+1,rng);
    for(int i=1;i<=n;i++) cout<<a[i]<<' ';
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