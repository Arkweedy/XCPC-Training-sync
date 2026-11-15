#include<bits/stdc++.h>

using ll = long long;
using i64 = long long;

using namespace std;
const int N = 8009;
const int M = 1e6 + 9; 
int a[N];
int s[M];
int n,m;
void solve()
{
    cin >> n >> m;
    for(int i = 2;i <= m;i++)
    {
        for(int j = i;j <= m;j += i) 
        {
            s[j]++;
        }
    }
    s[0] = m-1;
    for(int i = 1;i <= n;i++) cin >> a[i];
    ll ans = 0;

    for(int i = 1;i <= n;i++)
    {
        int l = i;
        int r = i + 1;
        int cur = 0;
        while(l >= 1 && r <= n)
        {
            cur = __gcd(cur,abs(a[l] - a[r]));
            l--;
            r++;
            ans += s[cur];
        }
    }
    for(int i = 1;i <= n;i++)
    {
        int l = i - 1;
        int r = i + 1;
        int cur = 0;
        while(l >= 1 && r <= n)
        {
            cur = __gcd(cur,abs(a[l] - a[r]));
            l--;
            r++;
            ans += s[cur];
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