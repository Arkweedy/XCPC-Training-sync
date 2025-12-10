#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n;
    cin>>n;
    string s;
    cin>>s;
    int a = 0, b = 0;
    s = '0' + s;
    for(int i = 1;i < s.length();i++){
        if(s[i] != s[i - 1]){
            if(s[i] == '0')a++;
            else b++;
        }
    }
    if(a >= 1)a--;
    if(b >= 2)b--;
    cout<<n+a+b<<endl;
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}