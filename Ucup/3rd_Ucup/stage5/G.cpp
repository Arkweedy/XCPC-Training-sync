#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

double fac(int x)
{
    double res = 1;
    for(int i = 2;i <= x;i++){
        res *= i;
    }
    return res;
}

void solve()
{
    for(int x = -25;x <= 25;x++){
        double expx = exp(x);
        double eps = 1e-9;
        int steps = 0;
        double res = 0;
        for(int i = 0;abs(expx - res) / expx > eps;i++){
            res += pow((double)x,i) / fac(i);
            steps = i;
        }
        cout<<"x = "<<x<<" need "<<steps<<" steps"<<endl;
    }

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