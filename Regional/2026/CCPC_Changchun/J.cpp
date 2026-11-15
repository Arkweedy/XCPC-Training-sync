#include<bits/stdc++.h>

using ll = long long;
using i64 = long long;

using namespace std;

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<int>a(n + 1);
    vector<int>x(m),y(m),z(m);
    for(int i = 0;i < m;i++){
        cin >> x[i] >> y[i] >> z[i];
        a[x[i]] |= z[i];
        a[y[i]] |= z[i];
    }
    i64 sum = 0;
    for(int i = 0;i < m;i++){
        if((a[x[i]] & a[y[i]]) != z[i]){
            cout << -1 << endl;
            return;
        }
    }

    for(int i = 1;i <= n;i++){
        sum += a[i];
    }
    cout << sum << endl;
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}