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
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    vector<int>p;
    p.push_back(114514);
    for(int i = 0;i < n;i++){
        if(i == n - 1 || a[i] > a[i + 1]){
            p.push_back(0);
        }
        else{
            p.push_back(1);
            i++;
        }
    }
    int m = p.size();
    vector<ll>ans(m),sumlen(m),cnt(m);
    for(int i = 1;i < m;i++){
        if(p[i] == 0){
            ans[i] = ans[i - 1] + sumlen[i - 1] + cnt[i - 1] + 1;
            sumlen[i] = sumlen[i - 1] + cnt[i - 1] + 1;
            cnt[i] = cnt[i - 1] + 1;
        }
        else{
            ans[i] = ans[i - 1] + sumlen[i - 1] * 2 + cnt[i - 1] * 2 + 3;
            sumlen[i] = sumlen[i - 1] + cnt[i - 1] + 2;
            cnt[i] = cnt[i - 1] + 2;
        }
    }
    
    cout<<ans[m - 1]<<endl;
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