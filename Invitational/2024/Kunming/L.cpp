#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

//Create time: 2025.11.02 17:47:55

void solve()
{
    int n, p, q;
    cin >> n >> p >> q;
    ll ans = 1ll * (p + q) * (p + 1) * (q + 1) / 2;
    vector<pair<int,int>>pos;
    for(int i = 0;i < n;i++){
        int x, y;
        cin>>x>>y;
        if(x < p && y < q)
        pos.emplace_back(x, y);
    }
    n = pos.size();
    sort(pos.begin(),pos.end(), [&](pair<int,int>x, pair<int,int>y)->bool
    {
        return x.first == y.first ? x.second > y.second : x.first < y.first;        
    });
    vector<vector<pair<int,int>>>que;
    vector<int>last;

    auto add = [&](int p, int x, int y)->void
    {
        if(que.size() == p){
            que.emplace_back();
            last.push_back(y);
        }
        que[p].emplace_back(x, y);
        last[p] = min(last[p],y);
        return;
    };

    if(n != 0){
        add(0, pos[0].first,pos[0].second);
    }

    for(int i = 1;i < n;i++){
        auto [x, y] = pos[i];
        int p = upper_bound(last.begin(),last.end(), y) - last.begin() - 1;//find below
        if(p == -1){
            add(p + 1, x, y);
        }
        else if(x == que[p][0].first){
            add(p, x, y);
        }
        else if(y == last[p]){
            add(p, x, y);
        }
        else{
            add(p + 1, x, y);
        }
    }

    vector<vector<int>>a(p + 1,vector<int>(q + 1));
    for(int i = 0;i < que.size();i++){
        auto v = que[i];
        for(auto [x, y] : v){
            a[x][y] = i + 1;
        }
    }

    for(int i = 0;i <= p;i++){
        for(int j = 0;j <= q;j++){
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }


    for(int i = 0;i < que.size();i++){
        int lasty = q + 1;
        for(auto [x, y] : que[i]){
            x++, y++;
            ans -= 1ll * (p - x + 1) * (lasty - y);
            lasty = y;
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