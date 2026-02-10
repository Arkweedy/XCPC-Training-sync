#include <bits/stdc++.h>
using namespace std;

using u32 = unsigned int;

struct FHQ {
    struct Node {
        int l = 0, r = 0;
        u32 pri = 0;
        int sz = 1;
        int val = 0;
        bool rev = false;
    };

    vector<Node> tr;
    mt19937 rng;

    FHQ(): rng((u32)chrono::steady_clock::now().time_since_epoch().count()) {
        tr.push_back(Node()); // 0 = null
    }

    int sz(int x) const { return x ? tr[x].sz : 0; }

    int newNode(int v) {
        tr.push_back(Node());
        int x = (int)tr.size() - 1;
        tr[x].pri = (u32)rng();
        tr[x].val = v;
        tr[x].sz  = 1;
        tr[x].l = tr[x].r = 0;
        tr[x].rev = false;
        return x;
    }

    void pull(int x) {
        tr[x].sz = 1 + sz(tr[x].l) + sz(tr[x].r);
    }

    void apply_rev(int x) {
        if(!x) return;
        swap(tr[x].l, tr[x].r);
        tr[x].rev ^= 1;
    }

    void push(int x) {
        if(!x || !tr[x].rev) return;
        apply_rev(tr[x].l);
        apply_rev(tr[x].r);
        tr[x].rev = false;
    }

    int merge(int a, int b) {
        if(!a || !b) return a ? a : b;
        if(tr[a].pri < tr[b].pri) {          // 小根堆
            push(a);
            tr[a].r = merge(tr[a].r, b);
            pull(a);
            return a;
        } else {
            push(b);
            tr[b].l = merge(a, tr[b].l);
            pull(b);
            return b;
        }
    }

    // split by rank: keep first k nodes in left part
    pair<int,int> split_by_rank(int x, int k) {
        if(!x) return {0, 0};
        push(x);
        if(sz(tr[x].l) >= k) {
            auto [a, b] = split_by_rank(tr[x].l, k);
            tr[x].l = b;
            pull(x);
            return {a, x};
        } else {
            auto [a, b] = split_by_rank(tr[x].r, k - sz(tr[x].l) - 1);
            tr[x].r = a;
            pull(x);
            return {x, b};
        }
    }

    void inorder(int x, vector<int> &out) {
        if(!x) return;
        push(x);
        inorder(tr[x].l, out);
        out.push_back(tr[x].val);
        inorder(tr[x].r, out);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    FHQ fhq;
    int root = 0;

    // build initial sequence 1..n
    for(int i = 1; i <= n; i++) {
        root = fhq.merge(root, fhq.newNode(i));
    }

    while(m--) {
        int l, r;
        cin >> l >> r;

        auto [A, C] = fhq.split_by_rank(root, r);
        auto [L, B] = fhq.split_by_rank(A, l - 1);
        fhq.apply_rev(B);
        root = fhq.merge(fhq.merge(L, B), C);
    }

    vector<int> ans;
    ans.reserve(n);
    fhq.inorder(root, ans);

    for(int i = 0; i < n; i++) {
        cout << ans[i] << (i + 1 == n ? '\n' : ' ');
    }
    return 0;
}
