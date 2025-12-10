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
    vector<ll>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }

    auto query = [&](std::vector<i64> &f, i64 x) {
        for (int i = 59; i >= 0; i--) {
            if ((x ^ f[i]) > x) {
                x ^= f[i];
            }
        }
        return x;
    };
    
    auto add = [&](std::vector<i64> &f, i64 x) {
        for (int i = 59; i >= 0; i--) {
            if (x >> i & 1) {
                if (!f[i]) {
                    f[i] = x;
                    return;
                }
                x ^= f[i];
            }
        }
    };

    ll ans = 0;
    auto dfs = [&](auto&&self,vector<ll>f, int p)->void
    {
        if(p >= n){
            ans = max(ans,query(f,0));
        }
        else{
            add(f, a[p]);
            self(self,f,p + 2);
            self(self,move(f),p + 3);
        }
    };
    dfs(dfs, vector<ll>(60), 0);
    dfs(dfs, vector<ll>(60), 1);
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