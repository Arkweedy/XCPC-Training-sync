#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//H.cpp Create time : 2026.05.09 20:18

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    vector<i64>c(n + 1);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    map<int,int>g;
    g[0] = 1;
    for(int i = 0;i < n;i++){
        map<int,int>ng;
        ng[0] = 1;
        for(auto [x, cnt] : g){
            int y = gcd(a[i], x);
            ng[y] += cnt;
            c[y] += cnt;
        }
        g = move(ng);
    }
    for(int i = 1;i <= n;i++){
        cout << c[i] << " ";
    }
    cout << endl;
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