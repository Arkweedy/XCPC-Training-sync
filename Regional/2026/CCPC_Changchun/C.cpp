#include<bits/stdc++.h>

using ll = long long;
using i64 = long long;

using namespace std;
const int N = 2e5 + 9;
int s[N];
int b[N];
int p[N];
int n,k;
void solve()
{
    cin >> n >> k;
    int cur = 0;
    s[0] = 0;
    for(int i = 1;i <= n;i++)
    {
        cin >> b[i];
        cur++;
        if(cur == k + 1) cur = 1;
        p[i] = cur;
        s[i] = 0;
    }
    for(int i = 1;i <= n;i++)
    {
        if(b[i] > k) continue;
        if(b[i] >= p[i]) s[b[i] - p[i]]++;
        else s[k - (p[i] - b[i])]++;
    }
    int ans = n;
    for(int i = 0 ;i <= n;i++)
    {
        ans = min(ans,n - s[i]);
    }
    cout << ans << '\n';
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