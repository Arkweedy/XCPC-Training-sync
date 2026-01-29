#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.01.29 15:22:09

void solve()
{
    int n;
    cin >> n;
    vector<int>mi(n), ma(n);
    for(int i = 0;i < n;i++){
        int k;
        cin >> k;
        vector<int>x(k);
        for(int i = 0;i < k;i++){
            cin >> x[i];
        }
        sort(x.begin(),x.end());
        mi[i] = x[0];
        ma[i] = x.back();
    }

    vector<int>p(n * 2);
    iota(i.begin(),i.end(), 0);
    
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