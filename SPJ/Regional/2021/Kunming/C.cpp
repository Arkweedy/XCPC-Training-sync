#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

template<typename T>
T power(T a, int p)
{
    T res = 1;
    while(p){
        if(p & 1)res *= a;
        a *= a;
        p>>=1;
    }
    return res;
}


void solve()
{
    double x;
    cin>>x;
    double ans = 0;
    double n = 1 / x;
    vector<double>fac(n + 1);
    fac[0] = 1;
    for(int i = 1;i <= n;i++){
        fac[i] = fac[i - 1] * i;
    }

    auto a = [&](int i)->double
    {
        return (1 - x * i) / x;
    };

    for(int i = 0;i < n;i++){
        ans += (i % 2 == 0 ? 1 : -1) * power(a(i), i) / fac[i] * exp(a(i));
    }

    cout<<fixed<<setprecision(12)<<ans<<endl;
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