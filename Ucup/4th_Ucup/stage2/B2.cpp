#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e5 + 10;

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<int>a(n),b(n);
    for(int i = 0;i < n;i++){
        cin>>a[i]>>b[i];
    }
    int len = 100 * k;
    constexpr ll inf = 1e14;
    vector<vector<ll>>dpx(k + 1,vector<ll>(len + 1, -inf)),dpy(k + 1,vector<ll>(len + 1, -inf));
    dpx[0][0] = dpy[0][0] = 0;
    for(int i = 0;i < n;i++){
        int x  = a[i], y = b[i];
        if(x <= y){
            for(int i = k - 1;i >= 0;i--){
                for(int j = 0;j + x <= len;j++){
                    dpx[i + 1][j + x] = max(dpx[i + 1][j + x], dpx[i][j] + y);
                }
            }
        }
        else{
            for(int i = k - 1;i >= 0;i--){
                for(int j = 0;j + y <= len;j++){
                    dpy[i + 1][j + y] = max(dpy[i + 1][j + y], dpy[i][j] + x);
                }
            }
        }
    }

    ll ans = 0;
    for(int i = 0;i <= k;i++){
        //(max, +) convolution
        auto f = dpx[i], g = dpy[k - i];

        for(int i = 0;i <= len;i++){
            for(int j = 0;j <= len;j++){
                if(f[i] >= 0 && g[j] >= 0){
                    //cerr<<i<<" "<<j<<" "<<f[i]<<" "<<g[j]<<endl;
                    ans = max(ans, (f[i] + j) * (g[j] + i));
                }
            }
        }

        //
        
        for(int i = len - 1;i >= 0;i--){
            f[i] = max(f[i], f[i + 1]);
            g[i] = max(g[i], g[i + 1]);
        }
    }
    cout<<ans<<endl;
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    cin>>tt;
    while(tt--){
        solve();
    }
    return 0;
}