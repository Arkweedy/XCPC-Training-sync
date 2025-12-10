#include <bits/stdc++.h>

using namespace std;
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
vector<pair<int, int>> prufer_to_edges(const vector<int> &p) {
    int n = p.size(), i, j, k;
    int m = n + 3;
    int cs[m];
    memset(cs, 0, sizeof cs);
    for (i = 0; i < n; i++) ++cs[p[i]];
    i = 0;
    while (cs[++i]);
    int u = i, v;
    vector<pair<int, int>> r;
    r.reserve(n);
    for (j = 0; j < n; j++) {
        cs[u] = 1e9;
        r.push_back({u, v = p[j]});
        if ((--cs[v] == 0) && (v < i)) u = v;
        if (v != u) {
            while (cs[i]) ++i;
            u = i;
        }
    }
    r.push_back({u, n + 2});
    return r;
}
const int debug = 0, K = 1e4;
struct actor {
    vector<vector<pair<int, int>>> e;
    vector<int> dist, dep, fa;
    vector<pair<int, int>> edges;
    map<pair<int, int>, int> ha;

    int cnt, n;
    void init(int n) {
        if (!debug) return;
        this->n = n;
        cnt = 0;
        vector<int> p(n - 2);
        for (int i = 0; i < n - 2; i++) p[i] = rng() % n + 1;
        edges = prufer_to_edges(p);
        e.assign(n + 1, {});
        dist.assign(n + 1, 0);
        dep.assign(n + 1, 0);
        fa.assign(n + 1, 0);
        ha.clear();
        for (auto [u, v] : edges) {
            int w = rng() % K + 1;
            ha[{u, v}] = ha[{v, u}] = w;
            e[u].push_back({v, w});
            e[v].push_back({u, w});
        }
        dfs(1, 0);
    }

    void init() {
        if (!debug) return;
        cnt = 0;
        n = 3;
        vector<array<int, 3>> t = {{1, 2, 3}, {1, 3, 1}};

        e.assign(n + 1, {});
        dist.assign(n + 1, 0);
        dep.assign(n + 1, 0);
        fa.assign(n + 1, 0);
        ha.clear();
        for (auto [u, v, w] : t) {
            ha[{u, v}] = ha[{v, u}] = w;
            e[u].push_back({v, w});
            e[v].push_back({u, w});
        }
        dfs(1, 0);
    }

    int lca(int u, int v) {
        while (u != v) {
            if (dep[u] < dep[v]) swap(u, v);
            u = fa[u];
        }
        return u;
    }

    int len(int u, int v) { return dist[u] + dist[v] - 2 * dist[lca(u, v)]; }

    void dfs(int u, int f) {
        fa[u] = f;
        for (auto [v, w] : e[u]) {
            if (v == f) continue;
            dist[v] = dist[u] + w;
            dep[v] = dep[u] + 1;
            dfs(v, u);
        }
    }

    int ask(int u, int v) {
        cnt++;
        //assert(cnt <= 7 * n);
        
        if (debug) {
            return len(u, v);
        } else {
            cout << "? " << u << ' ' << v << endl;
            int res;
            cin >> res;
            return res;
        }
    }

    void print() {
        for (auto [k, w] : ha) {
            cout << k.first << ' ' << k.second << ' ' << w << endl;
        }

        cout << "\n-------\n";
    }

    void out(vector<array<int, 3>> ans) {
        if (debug) {
            cout<<"ask "<<cnt<<" times"<<endl;
            //cout<<"ans : "<<endl;
            // for(auto [u, v, w] : ans){
            //     cout<<u<<" "<<v<<" "<<w<<endl;
            // }
            for (auto [u, v, w] : ans) {
                if (!ha.count({u, v})) {
                    cout << "err1\n";
                    print();
                    exit(0);
                } else if (ha[{u, v}] != w) {
                    cout << "err2\n";
                    print();
                    exit(0);
                }
            }
            cout<<"ok"<<endl;
        } else {
            cout << "! ";
            for (auto [u, v, w] : ans) {
                cout << u << ' ' << v << ' ' << w << ' ';
            }
            cout << endl;
        }
    }
};

void solve()
{
    int n;
    cin>>n;
    actor interactor;
    interactor.init();
    
    vector<array<int, 3>>ans;
    int root = rng() % n + 1;
    vector<int>d(n);
    for(int i = 1;i <= n;i++){
        if(i != root){
            int x = interactor.ask(root, i);
            d[i - 1] = x;
        }
        else{
            d[i - 1] = 0;
        }
    }
    vector<int>id(n);
    iota(id.begin(),id.end(), 1);

    auto get = [&](auto&&self, vector<int>idx, vector<int>dis, int root)->void
    // id -> idx in subtree  ; dis_i ->idx_i dis to root 
    {
        if(idx.size() == 1){
            return;
        }
        if(idx.size() == 2){
            ans.push_back({idx[0],idx[1],max(dis[0],dis[1])});
            return;
        }
        //cerr<<"in , size = " <<idx.size() <<endl;

        int m = idx.size();
        int maxdis = 0;
        int dia = -1;
        for(int i = 0;i < m;i++){
            if(maxdis < dis[i]){
                maxdis = dis[i];
                dia = idx[i];
            }
        }
        vector<int>dis2(m);
        for(int i = 0;i < m;i++){
            if(idx[i] != dia){
                dis2[i] = interactor.ask(idx[i],dia);
            }
            else{
                dis2[i] = 0;
            }
        }

        vector<int>dis_to_dia(m);
        for(int i = 0;i < m;i++){
            dis_to_dia[i] = (dis[i] + dis2[i] - maxdis) / 2;
        }

        map<int,vector<int>>subtree;
        map<int,vector<int>>subdis;
        map<int,int>subroot;
        vector<pair<int,int>>diam;
        for(int i = 0;i < m;i++){
            int x = dis[i] - dis_to_dia[i];
            subtree[x].push_back(idx[i]);
            subdis[x].push_back(dis_to_dia[i]);
            if(dis_to_dia[i] == 0){
                subroot[x] = idx[i];
                diam.emplace_back(x, idx[i]);
            }
        }

        //add self ans
        sort(diam.begin(),diam.end());
        assert(diam[0].first == 0);
        for(int i = 1;i < diam.size();i++){
            ans.push_back({diam[i].second, diam[i - 1].second, diam[i].first - diam[i - 1].first});
        }

        for(const auto& [d, r] : subroot){
            self(self, subtree[d], subdis[d], r);
        }
        return;
    };

    get(get,id,d,root);
    interactor.out(ans);
    
    return;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}