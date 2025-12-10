#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e5 + 10;
ll sum = 0;
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
        vector<pair<ll,ll>>f,g;
        for(int j=0;j<=len;j++){
            if(dpx[i][j]>0)f.push_back({j,dpx[i][j]});
            if(dpy[k-i][j]>0)g.push_back({dpy[k-i][j],j});
        }
        for(auto [x,y]:f)ans = max(ans,x*y);
        for(auto [x,y]:g)ans = max(ans,x*y);
        for(auto [u,v]:f){
            for(auto [x,y]:g){
                sum++;     
                ans = max(ans,(u+x)*(v+y));
            }
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

    cerr<<sum<<endl;
    return 0;
}