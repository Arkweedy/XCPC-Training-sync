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
    int l, r;
    cin>>l>>r;
    vector<string>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }
    vector<int>dis(n*m*2,-1),vs(n*m*2);
    queue<int>q;
    vector<int>dx = {1,1,1,0,0,-1,-1,-1}, dy = {1,0,-1,1,-1,1,0,-1};
    
    q.push(0);
    dis[0] = 0;
    auto ok = [&](int x, int y)->bool
    {
        return x >= 0 && y >= 0 && x < n && y < m && a[x][y] == '1';
    };
    while(!q.empty()){
        auto p = q.front();
        int oe = p / (n * m), x = p % (n * m) / m, y = p % m;
        //cerr<<oe<<" "<<x<<" "<<y<<endl;
        q.pop();
        for(int i = 0;i < 8;i++){
            int nx = x + dx[i], ny = y + dy[i];
            int np = n * m * (oe^1) + nx * m + ny ;
            //cerr<<nx<<" "<<ny<<" "<<np<<" "<<vs[np]<<endl;
            //if(ok(nx,ny))cerr<<"ok"<<endl;
            if(ok(nx,ny) && !vs[np]){
                vs[np] = 1;
                dis[np] = dis[p] + 1;
                q.push(np);
            }
        }
    }

    constexpr int inf = 1145141919;
    int emin = dis[n*m-1],omin = dis[n*m*2-1];
    if(emin == -1 && omin == -1){
        cout<<-1<<endl;
        return;
    }
    if(l < r){
        int ans = inf;
        if(emin != -1)ans = min(ans,(emin + r - 1)/r);
        if(omin != -1)ans = min(ans,(omin + r - 1)/r);
        cout<<ans<<endl;
    }else{
        if(r % 2 == 0){
            if(emin == -1){
                cout<<-1<<endl;
                return;
            }else{
                cout<<(emin + r - 1)/r<<endl;
                return;
            }
        }else{
            int ans = inf;
            if(emin != -1){
                int anse = (emin + r - 1)/r;
                if(anse % 2 == 1)anse++;
                ans = min(ans,anse);
            }
            if(omin != -1){
                int anso = (omin + r -1 )/r;
                if(anso % 2 == 0)anso++;
                ans = min(ans,anso);
            }
            cout<<ans<<endl;
        }
    }
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