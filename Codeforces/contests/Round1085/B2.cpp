#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.03.08 23:03:58

void solve()
{
    int n, m, l;
    cin >> n >> m >> l;
    vector<int>a(n + 1);
    for(int i = 1;i <= n;i++){
        cin >> a[i];
    }
    int reop = n;
    int sum = 0;
    a.push_back(l);
    for(int i = 1;i <= n + 1;i++){
        sum += a[i] - a[i - 1];
        if(i <= n){
            int c = min(m, reop + 1);
            int ave = (sum + c - 1) / c;
            reop--;
            sum -= ave;
        }
        cerr << sum << endl;
    }
    cout << sum << endl;
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