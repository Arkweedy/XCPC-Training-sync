#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n;
    cin>>n;
    vector<double>p(1<<n);
    int len = 1 << n;
    for(int i = 0;i < len;i++){
        cin>>p[i];
    }
    auto fzt = [&](vector<double>&a)->void
    {
        for(int i = 0;i < n;i++){
            for(int j = 0;j < len;j++){
                if(j >> i & 1){
                    a[j] += a[j ^ (1 << i)];
                }
            }
        }
    };
    auto fmt = [&](vector<double>&a)->void
    {
        for(int i = 0;i < n;i++){
            for(int j = len - 1;j >= 0;j--){
                if(j >> i & 1){
                    a[j] += a[j ^ (1 << i)];
                }
            }
        }
    };
    auto a = p;
    fzt(a);
    double ans = 0;
    int mask = len - 1;
    constexpr double eps = 1e-8;
    for(int i = 1;i < len;i++){
        if(abs(1 - a[mask ^ i] < eps)){
            cout<<"INF"<<endl;
            return;
        }
        ans += 1 / (1 - a[mask ^ i]) * (__popcount(i) % 2 == 0 ? -1 : 1);
    }
    cout << fixed << setprecision(8)<< ans<<endl;
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