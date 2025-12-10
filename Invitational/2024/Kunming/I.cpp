#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.11.02 15:00:44

void solve()
{
    string s;
    cin>>s;
    int n = s.length();
    int p = 0;
    if(count(s.begin(),s.end(), s[0]) == n){
        cout<<n / 2<<endl;
        return;
    }
    if(s[0] == s[n - 1]){
        p = n - 1;
        while(p > 0 && s[p] == s[0])p--;
        p++;
    }
    int la = s[p];
    vector<int>c(s.length() + 1);
    int len = 0;
    for(int i = 0;i < n;i++){
        if(s[(i + p) % n] == la){
            len++;
        }
        else{
            c[len]++;
            la = s[(i + p) % n];
            len = 1;
        }
    }
    c[len]++;
    len = 0;

    int ans = 0;
    int flg = 0;
    for(int i = 0;i <= n;i++){
        ans += (i / 2) * c[i];
        if(c[i] > 0 && i % 2 == 0)flg = 1;
    }
    if(flg)ans--;
    cout<<ans<<endl;
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