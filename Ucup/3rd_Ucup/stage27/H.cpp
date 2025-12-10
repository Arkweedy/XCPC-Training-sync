#include <bits/stdc++.h>

#define ll long long
using namespace std;
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

const int N = 1e6 + 10;

int n, m, q, p[N];

constexpr int ALPHA_SIZE = 30;
struct GSAM
{
    struct Node{
        array<int,ALPHA_SIZE>next;
        int link;
        int len;
        Node():next{},link{},len{}{}
    };
    vector<Node>t;
    static constexpr int root = 1;

    GSAM()
    {
        init();
    }

    void init()
    {
        t.assign(2,{});
        t[0].next.fill(1);
        t[0].len = -1;
    }

    int newNode()
    {
        t.emplace_back();
        return t.size() - 1;
    }

    int num(char c)
    {
        return c - 'a';
    }

    void insert(const vector<int>& v)//insert trie
    {
        int p = root;
        for(auto x : v){
            if(t[p].next[x] == 0){
                t[p].next[x] = newNode();
            }
            p = t[p].next[x];
        }
        return;
    }

    void insert(const string& s)//insert trie
    {
        int p = root;
        for(auto c : s){
            if(next(p,c) == 0){
                next(p,c) = newNode();
            }
            p = next(p,c);
        }
        return;
    }

    int insertSAM(int last, int x)//return last
    {
        int cur = t[last].next[x];
        t[cur].len = t[last].len + 1;
        int p = t[last].link;
        while(p != 0 && t[p].next[x] == 0){
            t[p].next[x] = cur;
            p = t[p].link;
        }
       
        if(p == 0){
            t[cur].link = 1;
        }
        else{
            int q = t[p].next[x];
            if(t[p].len + 1 == t[q].len){
                t[cur].link = q;
            }
            else{
                int clone = newNode();
              
                //t[clone].next = t[q].next;
                for(int i = 0;i < ALPHA_SIZE;i++){
                    t[clone].next[i] = t[t[q].next[i]].len != 0 ? t[q].next[i] : 0;
                }
                t[clone].link = t[q].link;
                t[clone].len = t[p].len + 1;
                while(p != 0 && t[p].next[x] == q){
                    t[p].next[x] = clone;
                    p = t[p].link;
                }
                t[q].link = t[cur].link = clone;
            }
        }
        return cur;
    }

    void build()
    {
        queue<pair<int,int>>q;
        for(int i = 0;i < ALPHA_SIZE;i++){
            if(t[root].next[i] != 0){
                q.push(make_pair(root,i));
            }
        }

        while(!q.empty()){
            auto [la, x] = q.front();
            q.pop();
            int last = insertSAM(la,x);
            for(int i = 0;i < ALPHA_SIZE;i++){
                if(t[last].next[i] != 0){
                    q.push(make_pair(last,i));
                }
            }
        }
    }

    inline int& next(const int& p,const char& c)noexcept
    {
        return t[p].next[num(c)];
    }

};


void solve() {
    cin >> n >> m >> q;
    if (n >= ALPHA_SIZE) {
        map<pair<int, int>, int> ha;
        vector<int> lst(n);
        vector<vector<pair<int, int>>> r(n);
        int idx = 0;
        for (int i = 1; i <= n; i++) {
            p[i] = i;
            if (i < n) ha[{i, i + 1}] = ++idx;
        }

        auto modify = [&](int u, int v, int x, int y, int t) -> void {
            int i = ha[{u, v}];
            r[i].push_back({lst[i], t - 1});
            if (!ha[{x, y}])
                ha[{x, y}] = ++idx, lst.push_back(0), r.push_back({});
            lst[ha[{x, y}]] = t;
        };

        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            if (u > 1) {
                modify(p[u - 1], p[u], p[u - 1], p[v], i);
            }
            if (v < n) {
                modify(p[v], p[v + 1], p[u], p[v + 1], i);
            }
            if (u + 1 == v) {
                modify(p[u], p[v], p[v], p[u], i);
            } else {
                modify(p[u], p[u + 1], p[v], p[u + 1], i);
                modify(p[v - 1], p[v], p[v - 1], p[u], i);
            }
            swap(p[u], p[v]);
        }

        for (int i = 1; i < n; i++) {
            int x = ha[{p[i], p[i + 1]}];
            r[x].push_back({lst[x], m});
        }

        auto merge = [](vector<pair<int, int>>& a,
                        vector<pair<int, int>>& b) -> vector<pair<int, int>> {
            vector<pair<int, int>> res;
            for (auto [l, r] : a) {
                for (auto [x, y] : b) {
                    if (x > r) break;
                    if (l <= y) {
                        res.emplace_back(max(l, x), min(y, r));
                    }
                }
            }
            sort(res.begin(), res.end());
            return res;
        };

        while (q--) {
            int k;
            cin >> k;
            vector<int> b(k);
            for (int i = 0; i < k; i++) cin >> b[i];
            // for (int i = 0; i < k; i++) cout << b[i] << ' ';
            // cout << endl;
            vector<pair<int, int>> res = {{0, m}};
            for (int i = 0; i + 1 < k; i++) {
                res = merge(res, r[ha[{b[i], b[i + 1]}]]);
            }
            cout << res[0].first << '\n';
        }

    } else {
        GSAM sam;
        vector<vector<int>>a(m + 1,vector<int>(n));
        iota(a[0].begin(),a[0].end(), 1);
        for(int i = 1;i <= m;i++){
            int u,v;
            cin>>u>>v;
            u--,v--;
            a[i] = a[i - 1];
            swap(a[i][u],a[i][v]);
        }
        for(int i = 0;i <= m;i++){
            sam.insert(a[i]);
        }
        sam.build();
        auto& t = sam.t;
        int len = t.size();
        constexpr int inf = 1145141919;
        vector<int>minpos(len, inf);
        for(int i = 0;i <= m;i++){
            int p = 1;
            for(int j = 0;j < n;j++){
                p = t[p].next[a[i][j]];
                minpos[p] = min(minpos[p],i);
            }
        }

        vector<vector<int>>ot(len);
        for(int i = 2;i < len;i++){
            ot[t[i].link].push_back(i);
        }
        auto dfs = [&](auto&&self, int p)->void
        {
            for(auto s : ot[p]){
                self(self, s);
                minpos[p] = min(minpos[p], minpos[s]);
            }
            return;
        };
        dfs(dfs,1);

        while(q--){
            int k;
            cin>>k;
            int p = 1;
            for(int i = 0;i < k;i++){
                int e;
                cin>>e;
                p = t[p].next[e];
            }
            cout<<minpos[p]<<"\n";
        }
    }
    return;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t = 1;
    while (t--) solve();
    return 0;
}