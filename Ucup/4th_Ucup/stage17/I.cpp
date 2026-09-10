#include<bits/stdc++.h>

using i64 = long long;
using ll = long long;

using namespace std;

struct DSU{
    int n;
    vector<int>fa,sz;

    DSU(int n_)
    {
        n = n_;
        fa.resize(n);
        iota(fa.begin(),fa.end(), 0);
        sz.resize(n, 1);
    }

    int find(int p)
    {
        return fa[p] == p ? p : (fa[p] = find(fa[p]));
    }

    void merge(int u, int v) // u <- v
    {
        int fu = find(u), fv = find(v);
        if(fu != fv)fa[fv] = fu;
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<set<pair<int,int>>>seg(n);
    for(int i = 0;i < n;i++){
        seg[i].insert(make_pair(i, i));
    }
    auto add = [&](int l, int r, int p)->void
    {
        auto it = seg[p].lower_bound({l, r});
        if(it != seg[p].end()){
            auto [rl, rr] = *it;
            if(rl == r + 1){
                r = rr;
                seg[p].erase(it);
            }
        }
        it = seg[p].lower_bound({l, r});
        if(it != seg[p].begin()){
            auto [Ll, lr] = *prev(it);
            if(lr + 1 == l){
                l = Ll;
                seg[p].erase(prev(it));
            }
        }
        seg[p].insert(make_pair(l, r));
    };

    DSU dsu(n);
    int ok1 = 1;
    set<int>nok;

    for(int i = 0;i < n - 1;i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        if(v != dsu.find(v)){
            ok1 = 0;
        }
        if(!ok1){
            cout << "Bad oriented forest" << endl;
            continue;
        }

        if(seg[u].size() < seg[v].size()){
            swap(seg[u], seg[v]);
        }
        for(auto [l, r] : seg[v]){
            add(l, r, u);
        }
        if(seg[u].size() > 1){
            nok.insert(u);
        }
        nok.erase(v);

        if(nok.empty()){
            cout << "Good" << endl;
        }
        else{
            int p = *nok.begin() + 1;
            cout << "Bad segment at " << p << endl;
        }
    }

    for(int i = 0;i < n;i++){
        cerr << "seg " << i << endl;
        for(auto [l, r] : seg[i]){
            cerr << l << " " << r << endl;
        }
    }

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
