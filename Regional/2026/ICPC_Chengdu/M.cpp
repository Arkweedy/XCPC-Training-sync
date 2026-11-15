#include<bits/stdc++.h>

using ll = long long;
using i64 = long long;
 
using namespace std;
const int N = 1e6 + 9;
int l[N];
int r[N];
int n;
void solve()
{
    cin >> n;
    for(int i = 1;i <= n;i++)
    {
        cin >> l[i] >> r[i];
    }
    int ans= 1;
    int cur = r[1];
    int jl = 2;
    while(jl <= n)
    {
        int jr = jl;
        while(jr <= n && l[jr] <= cur) jr++;
        if(jr <= n)
        {
            for(int i = jl;i <= jr;i++) cur = max(cur,r[i]);
            ans++;
        }
        jl = jr + 1;
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