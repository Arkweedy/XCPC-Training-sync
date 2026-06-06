#include<bits/stdc++.h>
using ll = long long;
using i64 = long long;

using namespace std;

int power(int a, i64 p, int m)
{
    if(m == 1)return 0;
    int res = 1 % m;
    while(p){
        if(p & 1)res = 1ll * res * a % m;
        a = 1ll * a * a % m;
        p >>= 1;
    }
    return res;
}

void solve()
{
    i64 n;
    int m, p;
    cin >> n >> m >> p;

    set<i64> s;
    s.insert(0);
    for(int i = 0;i < m;i++){
        i64 x;
        cin >> x;
        s.insert(x);
    }

    i64 cnt = n - *s.rbegin();
    while(s.size() > 1){
        auto itx = prev(s.end());
        i64 x = *itx;
        auto ity = prev(itx);
        i64 y = *ity;

        s.erase(itx);
        if(x >= 2 * y){
            cnt += (x + 1) / 2 - y;
        }
        else{
            s.insert(2 * y - x);
        }
    }

    cout << power(2, cnt, p) << '\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int tt = 1;
    while(tt--){
        solve();
    }
    return 0;
}
