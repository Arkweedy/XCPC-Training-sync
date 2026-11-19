#include <bits/stdc++.h>

using ll = long long;
using i64 = long long;

using namespace std;
const int N = 1e5 + 9;
int a[N];
int n;
void solve()
{
    cin >> n;
    for(int i = 1;i <= n;i++) cin >> a[i];
    int m = a[1];
    for(int i = 1;i <= n;i++) m = max(m,a[i]);
    if( (m % 2) == 0)
    {
        for(int i = 1;i <= n;i++)
        {
            if(a[i] == m)
            {
                cout << i << '\n';
                return;
            }
        }
    }
    else
    {
        for(int i = n;i >= 1;i--)
        {
            if(a[i] == m)
            {
                cout << i << '\n';
                return;
            }
        }
    }

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