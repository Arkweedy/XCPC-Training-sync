#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    string s;
    cin>>s;
    int cnt = count(s.begin(),s.end(),'T');
    string t(cnt,'T');
    for(int i = 0;i < s.length();i++){
        if(s[i] != 'T'){
            t += s[i];
        }
    }
    cout << t<<endl;
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