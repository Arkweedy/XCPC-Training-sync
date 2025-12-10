#include<bits/stdc++.h>

using namespace std;

using ll = long long;

constexpr int N = 1e5 + 10;
std::mt19937 g(std::chrono::steady_clock::now().time_since_epoch().count());

void check()
{
    static int cnt = 0;
    cnt++;
    int n = 100;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        a[i] = g() % 10;
    }
    int cap = 10 + g() % 100;
    int x = 0, y = 0;
    int sum = 0;
    for(int i = 0;i < n;i++){
        if(sum + a[i] <= cap){
            sum += a[i];
        }
        else{
            x++;
            sum = a[i];
        }
    }
    if(sum > 0){
        sum = 0;
        x++;
    }
    for(int i = n - 1;i >= 0 ;i--){
        if(sum + a[i] <= cap){
            sum += a[i];
        }
        else{
            y++;
            sum = a[i];
        }
    }
    if(sum > 0){
        sum = 0;
        y++;
    }
    assert(x == y && "dif !");
    cerr<<"check "<<cnt<<" ok"<<endl;
}

void solve()
{
    int n, m, V , T;
    cin>>n>>m>>V>>T;
    T--;
    vector<vector<pair<int,int>>>g(n);
    for(int i = 0;i < m;i++){
        int u, v, w;
        cin>>u>>v>>w;
        u--,v--;
        g[u].emplace_back(v,w);
        g[v].emplace_back(u,w);
    }
    
    constexpr int inf = 1e9;
    vector<pair<int,int>>dis(n, make_pair(inf,inf));
    priority_queue<array<int,3>,vector<array<int,3>>,greater<array<int,3>>>pq;
    
    pq.push({0,0,T});
    vector<int>vs(n);
    while(!pq.empty()){
        auto [cnt, rcap, p] = pq.top();
        pq.pop();
        if(vs[p])continue;
        vs[p] = 1;
        dis[p] = make_pair(cnt, rcap);
        
        for(auto [s ,w] : g[p]){
            if(!vs[s]){
                if(w + rcap > V){
                    pq.push({cnt+1, w, s});
                }
                else{
                    pq.push({cnt, w + rcap, s});
                }
            }
        }
    }
    
    vector<int>ans(n);
    for(int i = 0;i < n;i++){
        if(dis[i].first != inf){
            ans[i] = dis[i].first + 1;
        }
        else{
            ans[i] = -1;
        }
    }
    for(int i = 0;i < n;i++){
        cout<<ans[i]<<" ";
    }
    cout<<endl;
    return;
}

int main()
{
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int t = 1;
    //cin>>t;
    while(t--){
        solve();
    }
    return 0;
}
