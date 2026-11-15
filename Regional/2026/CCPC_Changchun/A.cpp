#include<bits/stdc++.h>

using ll = long long;
using i64 = long long;

using namespace std;

void solve()
{
    int n,m;
    cin >> n >> m;
    vector<vector<int>> v(n,vector<int>(m));
    ll ans = 0;
    for(int i = 0;i < n;i++) 
    {
        for(int j = 0;j  < m;j++)
        {
            cin >> v[i][j];
        }
    }
    for(int i = 0;i < n;i++) ans += v[i][0];

    for(int j = 1;j < m;j++)
    {
        vector<int> temp(n);
        vector<int> tt(n);
        for(int i = 0;i < n;i++) temp[i] = v[i][j];
        for(int i = 0;i < n;i++) tt[i] = v[i][j-1];
        int cur = n - 1;
        for(int i = n-1;i >= 0;i--)
        {
            while(cur >= 0 && cur >= i && temp[cur] <= tt[i])
            {
                tt[i] -= temp[cur];
                temp[cur] = 0;
                cur--;
            }


            if(cur < 0 || cur < i) continue;
            temp[cur] -= tt[i];
        }
        for(int i = 0;i < n;i++)
        {
            ans += temp[i];
        }
    }
    cout << ans << '\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}