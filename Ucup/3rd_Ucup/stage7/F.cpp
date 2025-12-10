#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;
using ld = long double;

using namespace std;

constexpr int P1 = 1e9 + 7;
constexpr int P2 = 1e9 + 9;

constexpr ld chv = (sqrtl(5) + 1) / 2;
constexpr ld lgchv = log10l(chv);

void solve()
{
    int n;
    cin>>n;
    vector<string>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    sort(a.begin(),a.end(),[&](const string& i ,const string& j)->bool
    {
        if(i.length() == j.length())return i < j;
        else return i.length() < j.length();
    });

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