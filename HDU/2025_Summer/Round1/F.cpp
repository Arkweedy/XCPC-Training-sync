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
    vector<vector<int>>a(n,vector<int>(m));
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            cin>>a[i][j];
        }
    }
    vector<int>indeg(n*m);
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m - 1;j++){
            if(a[i][j] > a[i][j + 1]){
                indeg[i*m+j+1]++;
            }
            else{
                indeg[i*m+j]++;
            }
        }
    }
    for(int i = 0;i < n - 1;i++){
        for(int j = 0;j < m;j++){
            if(a[i][j] > a[i+1][j]){
                indeg[i*m+m+j]++;
            }
            else{
                indeg[i*m+j]++;
            }
        }
    }
    vector<pair<int,int>>hi;
    if(indeg[0] != 0)hi.push_back({0,0});
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            if(indeg[i*m+j]==0){
                hi.emplace_back(i,j);
            }
        }
    }


    int len = hi.size();
    //vector<array<ll,3>>e;
    constexpr ll kx = 114, ky = 5141,kz = 919810;
    //x + y + z

    // auto add_edge = [&](int i, int j)->void
    // {
    //     e.push_back({abs_dis(hi[i],hi[j]), hi[i].first*m + hi[i].second, hi[j].first * m+hi[j].second});
    // };

    auto abs_dis = [&](const pair<int,int>& i, const pair<int,int>& j)->ll
    {
        return abs(i.first - j.first)*kx + abs(i.second - j.second)*ky + abs(a[i.first][i.second] - a[j.first][j.second])*kz;
    };

    sort(hi.begin(),hi.end(),[&](const pair<int,int>&i, const pair<int,int>&j)->bool
    {
        return a[i.first][i.second]<a[j.first][j.second];
    });
    ll ans = 0;
    ll val = 1ll << 34;
    ans += (len - 1) * val;
    for(int i = 0;i < len - 1;i++){
        ans += abs_dis(hi[i],hi[i + 1]);
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