#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n,m;
    cin >> n >> m;
    set<string> se;
    map<string,int> ma;
    for(int i = 1;i <= n;i++)
    {
        string ss;
        cin >> ss;
        se.insert(ss);
    }
    while(m--)
    {
        string ss;
        cin >> ss;
        if(se.count(ss))
        {
            if(ma[ss])
            {
                cout << "REPEAT\n";
            }
            else
            {
                ma[ss] = true;
                cout << "OK\n";
            }
        }
        else
        {
            cout << "WRONG\n";
        }
    }
}
int main()
{

    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}