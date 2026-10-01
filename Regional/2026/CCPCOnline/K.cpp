#include<bits/stdc++.h>

using i64 = long long;
using ll = long long;

using namespace std;

constexpr int P = 998244353;

int power(int a, int p)
{
    int res = 1;
    while(p){
        if(p & 1)res = 1ll * res * a % P;
        a = 1ll * a * a % P;
        p >>= 1;
    }
    return res;
}

int inv(int x)
{
    return power(x, P - 2);
}

void solve()
{
    int n, m, t;
    cin >> n >> m >> t;
    t--;
    string st;
    cin >> st;
    vector<int>pst(n);
    for(int i = 0;i < n;i++){
        pst[i] = st[i] - '0';
    }
    vector<vector<pair<int,int>>>g(n),rg(n);
    vector<int>outdeg(n);

    for(int i = 0;i < m;i++){
        int u, v, w;
        cin >> u >> v >> w;
        u--,v--;
        g[u].emplace_back(v, w);
        rg[v].emplace_back(u, w);
        outdeg[u]++;
    }

    vector<int>seq;
    queue<int>q;
    constexpr i64 inf = LLONG_MAX / 2;
    vector<i64>dis(n, inf);
    dis[t] = 0;
    q.push(t);

    
    
    while(!q.empty()){
        auto p = q.front();
        i64 d = dis[p];
        q.pop();
        seq.push_back(p);
        for(auto [s, w] : rg[p]){
            if(dis[p] + w < dis[s]){
                dis[s] = dis[p] + w;
            }
            outdeg[s]--;
            if(outdeg[s] == 0){
                q.push(s);
            }
        }
    }

    vector<vector<pair<int,int>>>tg(n);
    vector<int>pcnt(n);
    pcnt[t] = 1;

    for(auto p : seq){
        if(p == t)continue;
        for(auto [s, w] : g[p]){
            if(dis[p] == dis[s] + w){
                pcnt[p] = (pcnt[p] + pcnt[s]) % P;
                tg[p].emplace_back(s, w);
            }
        }
    }

    // for(int i = 0;i < n;i++){
    //     cerr << pcnt[i] << " ";
    // }
    // cerr << endl;

    // for(int i = 0;i < n;i++){
    //     cerr << "tg " << i + 1 << endl;
    //     for(auto x : tg[i]){
    //         cerr << x + 1 << " ";
    //     }
    //     cerr << endl;
    // }

    vector<i64>dp(n);

    for(auto p : seq){
        if(p == t)continue;
        if(pst[p] == 0){
            for(auto [s, w] : g[p]){
                dp[p] = ((i64)dp[p] + dp[s] + w) % P;
            }
            dp[p] = 1ll * dp[p] * inv(g[p].size()) % P;
        }
        else{
            for(auto [s, w] : tg[p]){
                dp[p] = (dp[p] + 1ll * (dp[s] + w) * pcnt[s]) % P;
            }
            dp[p] = 1ll * dp[p] * inv(pcnt[p]) % P;
        }
    }


    for(int i = 0;i < n;i++){
        cout << dp[i] << " ";
    }
    cout << endl;
    return;
}


int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}

