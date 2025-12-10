#include<bits/stdc++.h>

using namespace std;

using ll = long long;


constexpr ll INF = 1e18;
constexpr int mod = 1e9 + 7;
constexpr int N = 1e5 + 10;

void solve()
{
    int n, m;
    cin>>n>>m;
    vector<vector<int>>g(n);
    vector<int>vs(n);
    for(int i = 0;i < m;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
        vs[u] = vs[v] = 1;
    }
    for(int i = 0;i < n;i++){
        g[i].push_back((i + 1) % n);
        g[(i + 1) % n].push_back(i);
    }
    vector<int>clr(n, -1);

    queue<int>q;
    q.push(0);
    clr[0] = 1;
    // for(int i = 0;i < n;i++){
    //     if(vs[i]){
    //         clr[i] = 1;
    //         q.push(i);
    //         break;
    //     }
    // }

    while(!q.empty()){
        int p = q.front();
        q.pop();
        for(auto s : g[p]){
            if(clr[s] == -1){
                clr[s] = clr[p] ^ 1;
                q.push(s);
            }
        }
    }

    // for(int i = 0;i < n;i++){
    //     if(vs[i]){
    //         if(!vs[(i - 1 + n) % n])clr[(i - 1 + n) % n] = clr[i] ^ 1;
    //         if(!vs[(i + 1) % n])clr[(i + 1) % n] = clr[i] ^ 1;
    //     }
    // }

    //if(m == 0)clr[0] = 1;

    for(int i = 0;i < n;i++){
        cout<<(clr[i] == 1 ? 'R' : 'B');
    }
    cout<<endl;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}