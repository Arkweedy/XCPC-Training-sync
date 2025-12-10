#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;


void solve()
{
    int n,m;
    cin>>n>>m;
    vector<string>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }

    auto set = [&](vector<string>&a, int x, int y)->void
    {
        for(int i = x - 2;i <= x + 2;i++){
            if(i >= 0 && i < n)a[i][y] = 'H';
        }
        for(int j = y - 2;j <= y + 2;j++){
            if(j >= 0 && j < m)a[x][j] = 'H';
        }
    };

    auto ok = [&](vector<string>&a, int x, int y)->bool
    {
        return a[x][y] == 'P';
    };

    int ans = 0;
    auto dfs = [&](auto&&self,vector<string>&a, int x, int y,int cnt)->void
    {
        ans = max(ans,cnt);
        for(int j = y + 1;j < m;j++){
            if(ok(a,x,j)){
                auto b = a;
                set(b,x,j);
                self(self,b,x,j,cnt+1);
            }
        }
        for(int i = x + 1;i < n;i++){
            for(int j = 0;j < m;j++){
                if(ok(a,i,j)){
                    auto b = a;
                    set(b,i,j);
                    self(self,b,i,j,cnt+1);
                }
            }
        }
    };
    dfs(dfs,a,0,-1,0);
    cout<<ans<<endl;
    return;
}

int main()
{
    // freopen("dp.in","r",stdin);
    // freopen("dp.out","w",stdout);
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}