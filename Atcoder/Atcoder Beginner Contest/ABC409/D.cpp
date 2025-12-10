#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n;
    string s;
    cin>>n>>s;
    int l = -1,r = n - 1;
    for(int i = 0;i < n - 1;i++){
        if(s[i] > s[i + 1] && l == -1){
            l = i;
        }else if(l != -1 && s[i + 1] > s[l]){
            r = i;
            break;
        }
    }
    auto t = s;
    cerr<<l<<" "<<r<<endl;
    if(l != -1){
        for(int i = l;i < r;i++){
            t[i] = s[i + 1];
        }
        t[r] = s[l];
    }
    cout<<t<<endl;
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