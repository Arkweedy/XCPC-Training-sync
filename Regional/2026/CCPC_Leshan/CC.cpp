#include <bits/stdc++.h>

using ll = long long;
using i64 = long long;

using namespace std;
const int N = 1e9 + 7;
vector<int> a;
void solve()
{
    int n,k;
    cin >> n >> k;
    if(k != 1) n = (n/(k+1)) + 1;
    int ans = 1;
    for(int i = 0;i < a.size();i++)
    {
        if(n > a[i])
        {
            n -= a[i];
            ans ^= 1;
        }
    }
    if(ans) cout << "cat\n";
    else cout << "dog\n";
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    a.push_back(1);
    while(a.back() * 2 < N)
    {
        a.push_back(a.back() * 2);
    }
    reverse(a.begin(),a.end());
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}