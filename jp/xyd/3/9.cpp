#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,d;
    cin>>n>>d;
    vector<int>x(n),y(n);
    for(int i = 0;i < n;i++){
        cin>>x[i]>>y[i];
    }
    vector<pair<int,int>>range(n);
    for(int i = 0;i < n;i++){
        if(y[i] > d){
            cout<<-1<<endl;
            return;
        }
        int len = floorl(sqrtl(1ll * d * d - 1ll * y[i] * y[i]));
        range[i] = make_pair(x[i] - len, x[i] + len);
    }
    sort(range.begin(),range.end());
    int r = range[0].second;
    int ans = 0;
    range.emplace_back(1145141919,810);
    for(int i = 0;i <= n;i++){
        if(r < range[i].first){
            ans++;
            r = range[i].second;
        }
        else{
            r = min(r,range[i].second);
        }
    }
    cout<<ans<<endl;
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}