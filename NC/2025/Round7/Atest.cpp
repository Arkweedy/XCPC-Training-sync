#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int m, k ,n;
    cin>>m>>k>>n;
    //m = 100 , k = 10, n = 10
    vector<vector<vector<int>>>a(m,vector<vector<int>>(k,vector<int>(n * n)));
    for(int i = 0;i < m;i++){
        for(int j = 0;j < k;j++){
            for(int p = 0;p < n * n;p++){
                cin>>a[i][j][p];
                a[i][j][p]--;
            }
        }
    }

    auto check = [&](vector<int>&p)->bool
    {
        vector<int>vs(n * n);
        auto dfs = [&](auto&&self, int x)->int
        {
            if(vs[x])return 0;
            else{
                vs[x] = 1;
                return self(self, p[x]) + 1;
            }
        };
        int res = 0;
        for(int i = 0;i < n * n;i++){
            if(!vs[i]){
                res += dfs(dfs, i) - 1;
            }
        }
        return res % 2;//1->odd 0->even
    };

    string ans(m,'0');
    for(int i = 0;i < m;i++){
        for(int j = 0;j < k;j++){
            if(check(a[i][j])){
                ans[i] = '1';
                break;
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
    //while(tt--){
        solve();
    //}
    return 0;
}