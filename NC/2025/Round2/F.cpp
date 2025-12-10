#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n, t;
    cin>>n>>t;
    string s;
    cin>>s;
    s = s + s;
    int ma = 0;
    int cnt = 0;
    int l = -1;
    for(int i = 0;i < 2*n;i++){
        if(s[i] == '0'){
            cnt++;
        }
        else{
            if(cnt > ma){
                ma = max(ma,cnt);
                l = i - cnt - 1;
            }
            cnt = 0;
        }
    }
    cnt = 0;

    int ans = 0;
    for(int i = l;i <= l + n;i++){
        if(s[i] == '0'){
            cnt++;
        }
        else{
            ans += max(0, cnt - t * 2);
            cnt = 0;
        }
    }
    if(ma >= t * 2)ans += t - 1;
    else if(ma > t)ans += (ma - t - 1);
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