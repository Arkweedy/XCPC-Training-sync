#include <bits/stdc++.h>
using ll = long long;
using i64 = long long;
using namespace std;
const int N = 5e5 + 9;
int dep[N];
int jj[N];
int nex[N][26];
int maxone[N];

int cnt;
ll ans;
int n;
void cal(int cur)
{

    if(maxone[jj[cur]] < dep[cur])
    {
        ans -= maxone[jj[cur]] ^ jj[cur];
        ans += dep[cur] ^ jj[cur];
        maxone[jj[cur]] = dep[cur];
    }    
}
void solve()
{
    cin >> n;
    for(int i = 1;i <= n;i++)
    {
        string s;
        cin >> s;
        int cur = 0;
        ans += i;
        for(const char ch : s)
        {
            int id = ch - 'a';
            if(!nex[cur][id]) 
            {
                nex[cur][id] = ++cnt;
                dep[nex[cur][id]] = dep[cur] + 1;
            }    
            cur = nex[cur][id];      
            jj[cur]++;
            cal(cur);
        }
        cout << ans << '\n';
    }
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}