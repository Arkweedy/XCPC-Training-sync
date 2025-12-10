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
    vector<int>l(n),r(n);
    for(int i = 0;i < n;i++){
        cin>>l[i]>>r[i];
        r[i]++;
    }
    sort(l.begin(),l.end());
    sort(r.begin(),r.end());
    int p = -1e9-7;
    int pl = 0,pr = 0;
    int cnt = 0;
    int ans = 0;
    while(pr < n){
        if(pl == n)p = r[pr];
        else p = min(l[pl],r[pr]);
        while(pl < n && l[pl] == p){
            pl++;
            cnt++;
        }
        while(pr < n && r[pr] == p){
            pr++;
            cnt--;
        }
        ans = max(ans,cnt);
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