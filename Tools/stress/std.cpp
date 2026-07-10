#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>

using namespace std;

using i64 = long long;

using Heap = __gnu_pbds::priority_queue<
    i64,
    std::less<i64>,
    __gnu_pbds::pairing_heap_tag
>;

void solve() {
    int n;
    cin >> n;

    vector<i64> a(n);
    i64 sum = 0;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }

    vector<vector<int>> g(n);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // 建出以 0 为根的有根树，避免递归爆栈
    vector<int> parent(n, -2);
    vector<int> order;
    order.reserve(n);

    parent[0] = -1;

    stack<int> st;
    st.push(0);

    while (!st.empty()) {
        int u = st.top();
        st.pop();

        order.push_back(u);

        for (int v : g[u]) {
            if (v == parent[u]) continue;
            parent[v] = u;
            st.push(v);
        }
    }

    vector<Heap> heap(n);
    vector<i64> ev(n, 0);

    // 自底向上处理
    for (int idx = n - 1; idx >= 0; idx--) {
        int u = order[idx];

        i64 x = 0;

        // 合并所有儿子
        for (int v : g[u]) {
            if (parent[v] != u) continue;

            x += ev[v];

            // 这个 swap 不是必须的，但一般保留无害
            if (heap[u].size() < heap[v].size()) {
                heap[u].swap(heap[v]);
            }

            // join 会把 heap[v] 合并进 heap[u]，并清空 heap[v]
            heap[u].join(heap[v]);
        }

        i64 cur = a[u];

        // 三元组压缩：
        // cur, b, c -> cur - b + c
        while (heap[u].size() >= 2 && heap[u].top() >= cur) {
            i64 b = heap[u].top();
            heap[u].pop();

            i64 c = heap[u].top();
            heap[u].pop();

            cur = cur - b + c;
        }

        if (heap[u].empty() || heap[u].top() <= cur) {
            // cur 可以作为新的单点
            heap[u].push(cur);
        } else {
            // 此时 heap[u] 里只剩一个 b，并且 b > cur
            // (cur, b) 变成 ev(b - cur)
            i64 b = heap[u].top();
            heap[u].pop();

            x += b - cur;
        }

        ev[u] = x;
    }

    // 计算根的标准形对应的差值 D
    i64 diff = 0;
    int cnt = 0;

    while (!heap[0].empty()) {
        i64 x = heap[0].top();
        heap[0].pop();

        if (cnt % 2 == 0) diff += x;
        else diff -= x;

        cnt++;
    }

    // ev 的符号取决于前面单点个数的奇偶性
    if (cnt % 2 == 1) diff += ev[0];
    else diff -= ev[0];

    i64 ans = (sum + diff) / 2;
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}