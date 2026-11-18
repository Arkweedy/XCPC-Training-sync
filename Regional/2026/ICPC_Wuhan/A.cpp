#include<bits/stdc++.h>

using ll = long long;
using i64 = long long;

using namespace std;

void solve()
{
    string a = "yeshenle";
    string b = "zaoshanghao";
    int cnt = 1;
    int cur = 0;
    int n;
    cin >> n;
    while(n--)
    {
        string c;
        cin >> c;
        if(c == a)
        {
            if(cur == 0) cur = 0;
            else 
            {
                cur = 0;
                cnt++;
            }
        }
        else if(c == b)
        {
            if(cur == 0) cur = 1;
            else cur = 1;
        }
        else
        {
            
        }
    }
    cout << cnt << '\n';
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}