#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int w,h,s;
    cin>>w>>h>>s;
    vector<int>rem = {w,w,h,h};
    sort(rem.begin(),rem.end());
    
    auto calc = [&](vector<int>rem)->ll
    {
        ll ans = 0;
        for(int i = 0;i < 4;i++){
            ans += rem[i] / s;
            rem[i] %= s;
            if(rem[i] != 0){
                int x = s - rem[i];
                ans++;
                for(int j = i + 1;j < 4;j++){
                    if(rem[j] >= x){
                        rem[j] -= x;
                        break;
                    }
                }
            }
        }   
        return ans;
    };
    ll res = LLONG_MAX;
    for(int i = 0;i < 12;i++){
        res = min(res, calc(rem));
        next_permutation(rem.begin(),rem.end());
    }
    
    cout<<res<<"\n";
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