#include <bits/stdc++.h>

using ll = long long;
using i64 = long long;
#define int ll
using namespace std;
const int N = 2e5 + 9;
const int M = 60;
int cnt[N];
int n;
int f[M][M];
int c(int a,int b)
{
    if(b > a) return 0;
    if(a < M) return f[a][b];
    int ret = 1;
    for(int i = a;i >= a - b + 1;i--)
    {
        ret *= i;
    }
    for(int i = 1;i <= b;i++)
    {
        ret /= i;
    }
    return ret;
}
bool ck(int x)
{
    int cur = 0;
    int left = n;
    for(int i = 0;i <= n;i++)
    {
        int temp = c(x,i);
        cur += temp;
        if(cur < cnt[i]) return false;
        cur -= cnt[i];
        left -= cnt[i];
        if(cur >= left) return true;
    }
    return true;
}
void solve()
{
    cin >> n;
    for(int i = 0;i <= n;i++) cnt[i] = 0;
    for(int i = 1;i <= n;i++)
    {
        int a;
        cin >> a;
        cnt[min(a,n)]++;
    }
    int ans = -1;
    int l = 0,r = n;
    while(r >= l)
    {
        int mid = (l + r) >> 1;
        if(ck(mid))
        {
            ans = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
    cout << ans << '\n';
}

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    for(int i = 0;i < M;i++) f[i][0] = f[i][i] = 1;
    for(int i = 1;i < M;i++)
    {
        for(int j = 1;j < i;j++)
        {
            f[i][j] = f[i-1][j] + f[i-1][j-1];
        }
    }
    int tt = 1;
    cin >> tt;

    while(tt--){
        solve();
    }
    return 0;
}