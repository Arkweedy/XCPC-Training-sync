#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2026.03.08 22:03:06

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    string t = s;
    for(int i = 0;i + 2 < n;i++){
        if(t[i] == '1' && t[i + 2] == '1'){
            t[i + 1] = '1';
        }
    }
    int l = count(t.begin(),t.end(), '1');
    int r = 0;
    int c = 0;
    //cerr << t << endl;
    t += '0';
    for(int i = 0;i <= n;i++){
        if(t[i] == '1'){
            c++;
        }
        else{
            //cerr << c << endl;
            r += c - (c - 1) / 2;
            //cerr << r << endl;
            c = 0;
        }
    }
    cout << r << ' ' << l << endl;
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