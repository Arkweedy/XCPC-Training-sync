#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve() {
    double x;
    cin>>x;
    int m = (int)floor(1.0 / x + 1e-12);
    double ans = 0;
    for (int k = 0; k <= m; ++k) {
        double a = 1.0/x - k;                 // a_k
        // log(term) = k*log(a) - lgamma(k+1) + a
        double logterm;
        if (k == 0) logterm = a;              // 0*log(a) - lgamma(1) + a = a
        else if (a <= 0) {
            if (a == 0) logterm = -INFINITY;  // a^k = 0
            else continue;                    // 不会出现：k<=m 保证 a>=0
        } else {
            logterm = k*log(a) - lgamma(k+1.0) + a;
        }
        double term = exp(logterm);
        if (k & 1) ans -= term; else ans += term;
    }
    cout<<fixed<<setprecision(15)<<ans<<endl;
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