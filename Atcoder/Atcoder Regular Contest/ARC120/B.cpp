#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int P = 998244353;

void solve()
{
    int n,m;
    cin>>n>>m;
    vector<string>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    int ans = 1;
    for(int i = 0;i < n + m - 1;i++){
        int chr = 0, chb = 0;
        for(int j = 0;j <= i;j++){
            int x = j, y = i - j;
            if(x < n && y < m){
                if(a[x][y] == 'R')chr = 1;
                else if(a[x][y] == 'B')chb = 1;
            }
        }
        if(chr && chb)ans *= 0;
        else if(chr || chb)continue;
        else ans = ans * 2 % P;
    }
    cout<<ans<<endl;
    return;
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