#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.03.16 22:35:47

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    int p = 0;
    vector<int>c(n);
    c[0]++;
    for(int i = 0;i < n;i++){
        if(s[p] == 'R')p++;
        else p--;
        c[p]++;
    }
    
    int ans = n - count(c.begin(),c.end(), 0);
    cout << ans << endl;
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