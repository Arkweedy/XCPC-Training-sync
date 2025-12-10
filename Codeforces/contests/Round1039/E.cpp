#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,k;
    cin>>n>>k;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    pair<int,int>ans = {-1,-1};
    auto check = [&](int x)->bool
    {
        //cerr<<"check "<<x<<endl;
        vector<int>f(n);
        for(int i = 0;i < n;i++){
            if(a[i] >= x)f[i] = 1;
            else f[i] = -1;
        }
        // for(int i = 0; i < n;i++){
        //     cerr<<f[i]<<" ";
        // }
        // cerr<<endl;
        vector<int>pf(n);
        pf[0] = f[0];
        for(int i = 1;i < n;i++){
            pf[i] = pf[i - 1] + f[i];
        }
        int mi = 0;
        int mipos = 0;//l - 1
        for(int i = k - 1;i < n;i++){
            if(pf[i] - mi >= 0){
                ans = {mipos + 1,i + 1};
                return 1;
            }
            if(mi > pf[i - k + 1]){
                mi = pf[i - k + 1];
                mipos = i - k + 1 + 1;
            }
            
        }
        return false;
    };

    int l = -1, r = n + 1;
    while(r - l > 1){
        int m = l + r >> 1;
        if(check(m)){//m ok
            l = m;
        }
        else{
            r = m;
        }
    }
    cout<<l<<" "<<ans.first<<" "<<ans.second<<endl;
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