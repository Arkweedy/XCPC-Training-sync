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
    mt19937 g(chrono::steady_clock::now().time_since_epoch().count());
    vector<pair<int,int>>e(m);
    for(int i = 0;i < m;i++){
        cin>>e[i].first>>e[i].second;
        e[i].first--;
        e[i].second--;
    }
    int ans = 0;
    auto random_calc = [&]()->void
    {
        shuffle(e.begin(),e.end(),g);
        vector<int>deg(n);
        int res = 0;
        for(const auto &[u,v] : e){
            if(deg[u] < 2 && deg[v] < 2){
                deg[u]++;
                deg[v]++;
                res++;
            }
        }
        ans = max(ans, res);
    };

    int tt = n * n * 5e3;
    while(tt--){
        random_calc();
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