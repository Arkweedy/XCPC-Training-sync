#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;



void solve() 
{
    int n, m;
    cin>>n>>m;
    int len = 1 << 10;
    vector<int>vs(n * len);
    vector<vector<pair<int,int>>>g(n);
    for(int i = 0;i < m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        u--,v--;
        g[u].emplace_back(v,w);
    }
    queue<int>q;
    q.push(0);
    vs[0] = true;
    while(!q.empty()){
        auto x = q.front();
        q.pop();
        int p = x / len, v = x % len;
        for(const auto &[s, w] : g[p]){
            int id = s * len + (v ^ w);
            if(!vs[id]){
                vs[id] = true;
                q.push(id);
            }
        }
    }
    int ans = -1;
    for(int i = 0;i < len;i++){
        if(vs[(n - 1) * len + i]){
            ans = i;
            break;
        }
    }
    cout<<ans<<endl;
    return;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}