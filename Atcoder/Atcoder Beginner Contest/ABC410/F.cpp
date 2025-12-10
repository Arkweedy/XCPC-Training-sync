#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int h,w;
    cin>>h>>w;
    vector<string>s(h);
    for(int i = 0;i < h;i++){
        cin>>s[i];
    }
    if(h > w){
        swap(h,w);
        vector<string>ns(h,string(w, ' '));
        for(int i = 0;i < w;i++){
            for(int j = 0;j < h;j++){
                ns[j][i] = s[i][j];
            }
        }
        s = ns;
    }
    vector<vector<int>>a(h + 1,vector<int>(w + 1));
    for(int i = 0;i < h;i++){
        for(int j = 0;j < w;j++){
            a[i + 1][j + 1] = (s[i][j] == '.' ? 1 : -1);
        }
    }
    h++,w++;
    for(int i = 0;i < h;i++){
        for(int j = 0;j < w-1;j++){
            a[i][j + 1] += a[i][j];
        }
    }
    for(int i = 0;i < h-1;i++){
        for(int j = 0;j < w;j++){
            a[i + 1][j] += a[i][j];
        }
    }
    for(int i = 0;i < h;i++){
        for(int j = 0;j < w;j++){
            cerr<<a[i][j]<<" ";
        }
        cerr<<endl;
    }

    ll ans = 0;
    vector<int>cnt(h * w * 2 + 1, 0);
    int base = h * w;
    for(int i = 0;i < h;i++){
        for(int j = i + 1;j < h;j++){
            for(int k = 0;k < w;k++){
                cnt[a[j][k] - a[i][k] + base]++;
            }
            for(int k = 0;k < w;k++){
                ans += 1ll * cnt[a[j][k] - a[i][k] + base] * (cnt[a[j][k] - a[i][k] + base] - 1) / 2;
                cnt[a[j][k] - a[i][k] + base] = 0;
            }
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
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}