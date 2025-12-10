#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,m,k;
    cin>>n>>m>>k;
    vector<string>s(n);
    for(int i = 0;i < n;i++){
        cin>>s[i];
    }
    vector<vector<int>>a(n + 1,vector<int>(m + 1));
    int all = 0;
    for(int i=  0;i < n;i++){
        for(int j = 0;j < m;j++){
            a[i + 1][j + 1] = (s[i][j] == 'g' ? 1 : 0);
        }
    }
    for(int i = 0;i <= n;i++){
        for(int j = 0;j < m;j++){
            a[i][j + 1] += a[i][j];
        }
    }
    for(int i = 0;i < n;i++){
        for(int j = 0;j <= m;j++){
            a[i + 1][j] += a[i][j];
        }
    }

    int mi = 1145141919;

    auto calc = [&](int x, int y)->int
    {
        int l = max(x - k + 1, 0), r = min(x + k - 1, n - 1);
        int u = max(y - k + 1, 0), d = min(y + k - 1, m - 1);
        return a[r + 1][d + 1] + a[l][u] - a[r + 1][u] - a[l][d + 1];
    };

    // for(int i = 0;i < n;i++){
    //     for(int j  = 0;j < m;j++){
    //         cerr<<calc(i,j)<<" ";
    //     }
    //     cerr<<endl;
    // }

    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            if(s[i][j] == '.'){
                mi = min(mi,calc(i,j));
            }
        }
    }

    int ans = a[n][m] - mi;
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