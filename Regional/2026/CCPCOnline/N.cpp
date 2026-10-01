#include<bits/stdc++.h>

using i64 = long long;
using ll = long long;

using namespace std;

void solve()
{
    int a, b ;
    cin >> a >> b;
    string s;
    cin >> s;
    int t = ((s[0] - '0') * 10 + (s[1] - '0')) * 60 + (s[3] - '0') * 10 + (s[4] - '0');
    if(t >= 240){
        cout << "YES\n";
    }
    else if(b >= 50){
        cout << "YES\n";
    }
    else if(b * 5 >= a){
        cout << "YES\n";
    }
    else{
        cout << "NO\n";
    }
    return;
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

