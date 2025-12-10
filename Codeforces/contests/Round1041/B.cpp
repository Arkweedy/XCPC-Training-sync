#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,p;
    cin>>n>>p;
    string s;
    cin>>s;
    p--;
    int l = p - 1, r = p + 1;
    while(l >= 0 && s[l] == '.')l--;
    while(r < n && s[r] == '.')r++;
    //n - r + 1 + 1
    //l + 1
    int ans = max(
        min(l + 2, n - p),
        min(n - r + 1, p + 1)
    );
    cout<<ans<<endl;
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