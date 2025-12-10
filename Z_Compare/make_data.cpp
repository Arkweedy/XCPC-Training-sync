// random_prufer_gen.cpp
// 纯随机数据生成器：
//  - 树：用 Prüfer 序列生成（无多重边、无自环，连通，n-1 条边）
//  - 边权：均匀随机 [W_MIN, W_MAX]（int 范围内，非负，适配 Dijkstra）
//  - 传送边：均匀随机点对 (u != v)，允许重复（纯随机风格）
// 常量 N/M 可按需调节；SEED=0 表示用时间种子；DEDUP_TELE=true 可改成去重版

#include <bits/stdc++.h>
using namespace std;

static const int    N      = 5000;           // 点数（n ≤ 5000）
static const int    M      = 3500;          // 传送边条数（m ≤ 10000）
static const int    W_MIN  = 1;              // 边权下界（>=0）
static const int    W_MAX  = 1000000000;     // 边权上界（<= 1e9，int 安全）
static const uint64_t SEED = 0;              // 固定种子；=0 用时间种子
static const bool   DEDUP_TELE = false;      // 是否对传送边去重（纯随机建议 false）

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int n = N, m = M;
    if (n < 2) { cerr << "N must be >= 2\n"; return 0; }

    uint64_t seed = SEED ? SEED
                         : (uint64_t)chrono::high_resolution_clock::now().time_since_epoch().count();
    mt19937_64 rng(seed);
    uniform_int_distribution<int> node(1, n);
    uniform_int_distribution<int> wdist(W_MIN, W_MAX);

    // -------- 1) 输出 n m --------
    cout << n << ' ' << m << '\n';

    // -------- 2) 生成 Prüfer 序列 --------
    vector<int> prufer(n - 2);
    for (int i = 0; i < n - 2; ++i) prufer[i] = node(rng);

    // 由 Prüfer 序列构造树（标准方法：度数+小根堆叶子）
    vector<int> deg(n + 1, 1);
    for (int x : prufer) ++deg[x];

    priority_queue<int, vector<int>, greater<int>> leaves;
    for (int v = 1; v <= n; ++v) if (deg[v] == 1) leaves.push(v);

    vector<tuple<int,int,int>> edges;
    edges.reserve(n - 1);

    for (int x : prufer) {
        int u = leaves.top(); leaves.pop();
        int v = x;
        // 随机边权
        edges.emplace_back(u, v, wdist(rng));
        if (--deg[v] == 1) leaves.push(v);
        // u 的度已减到 0，不再入堆
    }
    // 剩余两点
    int a = leaves.top(); leaves.pop();
    int b = leaves.top(); leaves.pop();
    edges.emplace_back(a, b, wdist(rng));

    // 随机打乱树边输出顺序（可选）
    shuffle(edges.begin(), edges.end(), rng);

    // -------- 3) 输出树边 --------
    for (auto [u, v, w] : edges) {
        cout << u << ' ' << v << ' ' << w << '\n';
    }

    // -------- 4) 生成传送边（纯随机点对，允许重复）--------
    if (!DEDUP_TELE) {
        for (int i = 0; i < m; ++i) {
            int u, v;
            do { u = node(rng); v = node(rng); } while (u == v);
            cout << u << ' ' << v << '\n';
        }
    } else {
        // 去重版本（如果你想避免大量重复）
        struct PairHash {
            size_t operator()(const uint64_t& x) const { return std::hash<uint64_t>{}(x); }
        };
        unordered_set<uint64_t, PairHash> seen;
        seen.reserve(m * 2);
        auto enc = [&](int x, int y)->uint64_t {
            if (x > y) swap(x, y);                 // 无向去重
            return (uint64_t)x * (n + 1ull) + (uint64_t)y;
        };
        vector<pair<int,int>> tele; tele.reserve(m);
        while ((int)tele.size() < m) {
            int u = node(rng), v = node(rng);
            if (u == v) continue;
            uint64_t key = enc(u, v);
            if (seen.insert(key).second) tele.emplace_back(u, v);
        }
        shuffle(tele.begin(), tele.end(), rng);
        for (auto [u, v] : tele) cout << u << ' ' << v << '\n';
    }

    return 0;
}
