#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.12.10 17:08:14

void solve()
{
    int n;
    cin >> n;
    auto ask = [&](int l ,int r)-> int
    {
        cout << "? " << l << " " << r << endl;
        int x;
        cin >> x;
        return x;
    };

    int res = ask(1, n / 2);
    if(res == 1){
        int l = n / 2, r = n;
        while(r - l > 1){
            int m = l + r >> 1;
            int ret = ask(1, m);
            if(ret == res){
                l = m;
            }
            else{//0
                r = m;
            }
        }
        cout << r << endl;
        return;
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