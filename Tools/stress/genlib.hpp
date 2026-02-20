// genlib.hpp (header-only implementation)
// C++20+

#pragma once

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstdint>
#include <iosfwd>
#include <numeric>
#include <queue>
#include <random>
#include <span>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace gen {

using i64 = long long;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using default_engine = std::mt19937_64;

// ============================================================================
// rnd: random primitives & distributions (std-based)
// ============================================================================
namespace rnd {

inline default_engine& rng() noexcept {
    // No explicit seed API: auto-init.
    static thread_local default_engine eng([] {
        std::random_device rd;
        const auto now = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        // Mix a few rd calls (some platforms are deterministic; this still works fine).
        u64 s = (u64)now;
        s ^= (u64)rd() + 0x9e3779b97f4a7c15ULL + (s << 6) + (s >> 2);
        s ^= (u64)rd() + 0x9e3779b97f4a7c15ULL + (s << 6) + (s >> 2);
        s ^= (u64)rd() + 0x9e3779b97f4a7c15ULL + (s << 6) + (s >> 2);
        return default_engine(s);
    }());
    return eng;
}

template <class T>
using uniform_distribution_t = std::conditional_t<
    std::is_integral_v<T>,
    std::uniform_int_distribution<T>,
    std::uniform_real_distribution<T>
>;

template <class T>
inline uniform_distribution_t<T> uniform_distribution(T l, T r) {
    return uniform_distribution_t<T>(l, r);
}

template <class T, class Engine>
inline T uniform(T l, T r, Engine& eng) {
    uniform_distribution_t<T> dist(l, r);
    return dist(eng);
}

template <class T>
inline T uniform(T l, T r) {
    return uniform<T>(l, r, rng());
}

inline int randint(int l, int r) { return uniform<int>(l, r); }
inline u32 rand_u32(u32 l, u32 r) { return uniform<u32>(l, r); }
inline i64 rand_i64(i64 l, i64 r) { return uniform<i64>(l, r); }
inline u64 rand_u64(u64 l, u64 r) { return uniform<u64>(l, r); }

//inline double rand_double(double l, double r) { return uniform<double>(l, r); }
inline double rand_double(double l = 0.0, double r = 1.0) { return uniform<double>(l, r); }

inline bool rand_bool(double p) {
    std::bernoulli_distribution dist(p);
    return dist(rng());
}

template <class T, class Engine>
inline const T& choice(std::span<const T> a, Engine& eng) {
    assert(!a.empty());
    auto idx = uniform<std::size_t>(0, a.size() - 1, eng);
    return a[idx];
}

template <class T>
inline const T& choice(std::span<const T> a) {
    return choice<T>(a, rng());
}

template <class It, class Engine>
inline void shuffle(It first, It last, Engine& eng) {
    std::shuffle(first, last, eng);
}

template <class It>
inline void shuffle(It first, It last) {
    std::shuffle(first, last, rng());
}

} // namespace rnd

// ============================================================================
// sample: permutations / sampling utilities
// ============================================================================
namespace sample {

template <class Engine>
inline std::vector<int> perm(int n, Engine& eng, int base) {
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), base);
    rnd::shuffle(p.begin(), p.end(), eng);
    return p;
}

inline std::vector<int> perm(int n, int base) {
    return perm(n, rnd::rng(), base);
}

template <class Engine>
inline std::vector<int> perm1(int n, Engine& eng) {
    return perm(n, eng, 1);
}

inline std::vector<int> perm1(int n) {
    return perm(n, 1);
}

// Floyd sampling for k distinct numbers from [0..N-1], O(k) expected.
// Then shift by l.
template <class Engine>
inline std::vector<int> distinct_ints(int k, int l, int r, Engine& eng) {
    assert(l <= r);
    const long long Nll = 1LL * r - l + 1;
    assert(Nll >= k);
    const int N = (int)Nll;

    std::vector<int> res;
    res.reserve(k);

    // For small N or dense sample, shuffle-all is simpler & fast.
    const long long enum_threshold = 3'000'000; // total edges-ish scale; here for ints too
    if ((long long)N <= enum_threshold && (long long)k * 3 >= (long long)N) {
        std::vector<int> all(N);
        std::iota(all.begin(), all.end(), l);
        rnd::shuffle(all.begin(), all.end(), eng);
        all.resize(k);
        return all;
    }

    // Floyd: sample k distinct indices in [0..N-1].
    std::unordered_map<int, int> mp;
    mp.reserve((std::size_t)k * 2);

    for (int i = N - k; i < N; i++) {
        int t = rnd::uniform<int>(0, i, eng);
        auto get = [&](int x) -> int {
            auto it = mp.find(x);
            return it == mp.end() ? x : it->second;
        };
        int x = get(t);
        int y = get(i);
        mp[t] = y;
        res.push_back(x + l);
    }
    // res is distinct but unordered
    return res;
}

inline std::vector<int> distinct_ints(int k, int l, int r) {
    return distinct_ints(k, l, r, rnd::rng());
}

template <class Engine>
inline std::vector<int> subset(int n, int k, Engine& eng, bool sorted, int base) {
    assert(0 <= k && k <= n);
    auto v = distinct_ints(k, base, base + n - 1, eng);
    if (sorted) std::sort(v.begin(), v.end());
    return v;
}

inline std::vector<int> subset(int n, int k, bool sorted, int base) {
    return subset(n, k, rnd::rng(), sorted, base);
}

} // namespace sample

// ============================================================================
// seq: arrays / intervals / monotone sequences
// ============================================================================
namespace seq {

template <class T, class Engine>
inline std::vector<T> array(int n, T l, T r, Engine& eng) {
    std::vector<T> a(n);
    for (int i = 0; i < n; i++) a[i] = rnd::uniform<T>(l, r, eng);
    return a;
}

template <class T>
inline std::vector<T> array(int n, T l, T r) {
    return array<T>(n, l, r, rnd::rng());
}

template <class T, class Engine>
inline std::vector<T> array_distinct(int n, T l, T r, Engine& eng) {
    static_assert(std::is_integral_v<T>, "array_distinct<T>: T must be integral");
    assert(l <= r);
    const long long Nll = (long long)r - (long long)l + 1;
    assert(Nll >= n);
    auto v = sample::distinct_ints(n, (int)l, (int)r, eng);
    std::vector<T> res(n);
    for (int i = 0; i < n; i++) res[i] = (T)v[i];
    return res;
}

template <class T>
inline std::vector<T> array_distinct(int n, T l, T r) {
    return array_distinct<T>(n, l, r, rnd::rng());
}

template <class T, class Engine>
inline std::vector<T> non_decreasing(int n, T l, T r, Engine& eng) {
    auto a = array<T>(n, l, r, eng);
    std::sort(a.begin(), a.end());
    return a;
}

template <class T>
inline std::vector<T> non_decreasing(int n, T l, T r) {
    return non_decreasing<T>(n, l, r, rnd::rng());
}

template <class T, class Engine>
inline std::vector<T> strictly_increasing(int n, T l, T r, Engine& eng) {
    static_assert(std::is_integral_v<T>, "strictly_increasing<T>: T must be integral");
    auto a = array_distinct<T>(n, l, r, eng);
    std::sort(a.begin(), a.end());
    return a;
}

template <class T>
inline std::vector<T> strictly_increasing(int n, T l, T r) {
    return strictly_increasing<T>(n, l, r, rnd::rng());
}

template <class T, class Engine>
inline std::pair<T, T> interval(T l, T r, Engine& eng, bool ordered, bool allow_empty) {
    assert(l <= r);
    T L, R;
    if (!allow_empty && ordered) {
        // generate L<=R directly
        L = rnd::uniform<T>(l, r, eng);
        R = rnd::uniform<T>(L, r, eng);
        return {L, R};
    }
    // otherwise: independent endpoints
    L = rnd::uniform<T>(l, r, eng);
    R = rnd::uniform<T>(l, r, eng);
    if (ordered && L > R) std::swap(L, R);
    return {L, R};
}

template <class T>
inline std::pair<T, T> interval(T l, T r, bool ordered, bool allow_empty) {
    return interval<T>(l, r, rnd::rng(), ordered, allow_empty);
}

template <class T, class Engine>
inline std::vector<std::pair<T, T>> intervals(int m, T l, T r, Engine& eng, bool ordered, bool allow_empty) {
    std::vector<std::pair<T, T>> res;
    res.reserve(m);
    for (int i = 0; i < m; i++) res.push_back(interval<T>(l, r, eng, ordered, allow_empty));
    return res;
}

template <class T>
inline std::vector<std::pair<T, T>> intervals(int m, T l, T r, bool ordered, bool allow_empty) {
    return intervals<T>(m, l, r, rnd::rng(), ordered, allow_empty);
}

} // namespace seq

// ============================================================================
// graph: trees / graphs
// ============================================================================
namespace graph {

using edge = std::pair<int, int>;

inline u64 pack_undirected(int a, int b) {
    if (a > b) std::swap(a, b);
    return (u64)(u32)a << 32 | (u32)b;
}

inline std::vector<edge> tree_chain(int n, int base, bool shuffle_edges) {
    assert(n >= 1);
    std::vector<edge> e;
    e.reserve(std::max(0, n - 1));
    for (int i = 0; i + 1 < n; i++) {
        e.emplace_back(base + i, base + i + 1);
    }
    if (shuffle_edges) rnd::shuffle(e.begin(), e.end());
    return e;
}

inline std::vector<edge> tree_star(int n, int center, int base, bool shuffle_edges) {
    assert(n >= 1);
    assert(base <= center && center <= base + n - 1);
    std::vector<edge> e;
    e.reserve(std::max(0, n - 1));
    for (int i = 0; i < n; i++) {
        int v = base + i;
        if (v == center) continue;
        e.emplace_back(center, v);
    }
    if (shuffle_edges) rnd::shuffle(e.begin(), e.end());
    return e;
}

inline std::vector<edge> tree_kary(int n, int k, int base, bool shuffle_edges) {
    assert(n >= 1);
    assert(k >= 1);
    std::vector<edge> e;
    e.reserve(std::max(0, n - 1));
    for (int i = 1; i < n; i++) {
        int p = (i - 1) / k;
        e.emplace_back(base + p, base + i);
    }
    if (shuffle_edges) rnd::shuffle(e.begin(), e.end());
    return e;
}

template <class Engine>
inline std::vector<edge> tree_prufer(int n, Engine& eng, int base, bool shuffle_edges) {
    assert(n >= 1);
    if (n == 1) return {};
    if (n == 2) {
        std::vector<edge> e = { {base, base + 1} };
        if (shuffle_edges) rnd::shuffle(e.begin(), e.end(), eng);
        return e;
    }

    // Prufer sequence values are labels in [base..base+n-1].
    std::vector<int> pr(n - 2);
    for (int i = 0; i < n - 2; i++) pr[i] = rnd::uniform<int>(base, base + n - 1, eng);

    std::vector<int> deg(n, 1);
    for (int x : pr) deg[x - base]++;

    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    for (int i = 0; i < n; i++) if (deg[i] == 1) pq.push(base + i);

    std::vector<edge> edges;
    edges.reserve(n - 1);

    for (int x : pr) {
        int leaf = pq.top(); pq.pop();
        edges.emplace_back(leaf, x);
        int xi = x - base;
        int li = leaf - base;
        deg[xi]--;
        deg[li]--;
        if (deg[xi] == 1) pq.push(x);
    }

    // last two leaves
    int a = pq.top(); pq.pop();
    int b = pq.top(); pq.pop();
    edges.emplace_back(a, b);

    if (shuffle_edges) rnd::shuffle(edges.begin(), edges.end(), eng);
    return edges;
}

inline std::vector<edge> tree_prufer(int n, int base, bool shuffle_edges) {
    return tree_prufer(n, rnd::rng(), base, shuffle_edges);
}

template <class Engine>
inline std::vector<edge> tree_random_parent(int n, Engine& eng, int base, bool shuffle_edges) {
    assert(n >= 1);
    std::vector<edge> e;
    e.reserve(std::max(0, n - 1));
    for (int i = 1; i < n; i++) {
        int v = base + i;
        int p = rnd::uniform<int>(base, v - 1, eng);
        e.emplace_back(p, v);
    }
    if (shuffle_edges) rnd::shuffle(e.begin(), e.end(), eng);
    return e;
}

inline std::vector<edge> tree_random_parent(int n, int base, bool shuffle_edges) {
    return tree_random_parent(n, rnd::rng(), base, shuffle_edges);
}

template <class Engine>
inline void relabel_edges_inplace(std::vector<edge>& edges, int n, Engine& eng, int base) {
    // Create a random bijection on [base..base+n-1]
    auto p = sample::perm(n, eng, base);
    auto mapv = [&](int x) -> int { return p[x - base]; };
    for (auto& [u, v] : edges) {
        u = mapv(u);
        v = mapv(v);
    }
}

inline void relabel_edges_inplace(std::vector<edge>& edges, int n, int base) {
    relabel_edges_inplace(edges, n, rnd::rng(), base);
}

// Helper: enumerate all undirected edges for small n
inline std::vector<edge> enumerate_all_edges_undirected(int n, int base) {
    std::vector<edge> all;
    all.reserve((std::size_t)n * (n - 1) / 2);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            all.emplace_back(base + i, base + j);
        }
    }
    return all;
}

template <class Engine>
inline std::vector<edge> simple_graph(int n, int m, Engine& eng, bool connected, int base, bool shuffle_edges) {
    assert(n >= 1);
    if (n == 1) { assert(m == 0); return {}; }
    const long long maxE = 1LL * n * (n - 1) / 2;
    assert(0 <= m && (long long)m <= maxE);
    if (connected) assert(m >= n - 1);

    // Dense small case: enumerate then shuffle
    const long long enum_threshold = 3'000'000; // max edges to enumerate
    if (maxE <= enum_threshold && (long long)m * 3 >= maxE) {
        auto all = enumerate_all_edges_undirected(n, base);
        rnd::shuffle(all.begin(), all.end(), eng);
        all.resize(m);

        if (connected) {
            // Ensure connected by forcing a random tree subset + extra edges.
            // For dense case, easiest: build tree, then fill remaining from shuffled all.
            auto tree = tree_prufer(n, eng, base, false);
            std::unordered_set<u64> st;
            st.reserve((std::size_t)m * 2);
            std::vector<edge> res;
            res.reserve(m);

            for (auto [u, v] : tree) {
                u64 key = pack_undirected(u, v);
                if (st.insert(key).second) res.emplace_back(u, v);
            }
            for (auto [u, v] : all) {
                if ((int)res.size() == m) break;
                u64 key = pack_undirected(u, v);
                if (st.insert(key).second) res.emplace_back(u, v);
            }
            if (shuffle_edges) rnd::shuffle(res.begin(), res.end(), eng);
            return res;
        }

        if (shuffle_edges) rnd::shuffle(all.begin(), all.end(), eng);
        return all;
    }

    // Sparse-ish: hash sampling
    std::unordered_set<u64> st;
    st.reserve((std::size_t)m * 2 + 16);

    std::vector<edge> res;
    res.reserve(m);

    if (connected) {
        auto tree = tree_prufer(n, eng, base, false);
        for (auto [u, v] : tree) {
            u64 key = pack_undirected(u, v);
            if (st.insert(key).second) res.emplace_back(u, v);
        }
    }

    int tries = 0;
    const int max_tries = std::max(100000, m * 50 + 1000);
    while ((int)res.size() < m) {
        int u = rnd::uniform<int>(base, base + n - 1, eng);
        int v = rnd::uniform<int>(base, base + n - 1, eng);
        if (u == v) {
            if (++tries > max_tries) break;
            continue;
        }
        u64 key = pack_undirected(u, v);
        if (st.insert(key).second) {
            res.emplace_back(u, v);
        } else {
            if (++tries > max_tries) break;
        }
    }

    // Fallback: if collisions were too high, and n small enough, enumerate.
    if ((int)res.size() < m) {
        if (maxE <= enum_threshold) {
            auto all = enumerate_all_edges_undirected(n, base);
            rnd::shuffle(all.begin(), all.end(), eng);
            for (auto [u, v] : all) {
                if ((int)res.size() == m) break;
                u64 key = pack_undirected(u, v);
                if (st.insert(key).second) res.emplace_back(u, v);
            }
        } else {
            // For huge dense requests, sampling without enumeration may be slow.
            // Here we assert to avoid silently returning fewer edges.
            assert((int)res.size() == m && "simple_graph: unable to sample enough unique edges");
        }
    }

    if (shuffle_edges) rnd::shuffle(res.begin(), res.end(), eng);
    return res;
}

inline std::vector<edge> simple_graph(int n, int m, bool connected, int base, bool shuffle_edges) {
    return simple_graph(n, m, rnd::rng(), connected, base, shuffle_edges);
}

template <class Engine>
inline std::vector<edge> connected_graph(int n, int m, Engine& eng, int base, bool shuffle_edges) {
    return simple_graph(n, m, eng, true, base, shuffle_edges);
}

inline std::vector<edge> connected_graph(int n, int m, int base, bool shuffle_edges) {
    return simple_graph(n, m, rnd::rng(), true, base, shuffle_edges);
}

// Enumerate all DAG edges for small n given order ord: edges ord[i] -> ord[j] for i<j
inline std::vector<edge> enumerate_all_dag_edges(const std::vector<int>& ord) {
    const int n = (int)ord.size();
    std::vector<edge> all;
    all.reserve((std::size_t)n * (n - 1) / 2);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            all.emplace_back(ord[i], ord[j]);
        }
    }
    return all;
}

inline u64 pack_directed(int u, int v) {
    return (u64)(u32)u << 32 | (u32)v;
}

template <class Engine>
inline std::vector<edge> dag(int n, int m, Engine& eng, int base, bool shuffle_edges) {
    assert(n >= 1);
    const long long maxE = 1LL * n * (n - 1) / 2;
    assert(0 <= m && (long long)m <= maxE);

    // Random topological order
    auto ord = sample::perm(n, eng, base);

    const long long enum_threshold = 3'000'000;
    if (maxE <= enum_threshold && (long long)m * 3 >= maxE) {
        auto all = enumerate_all_dag_edges(ord);
        rnd::shuffle(all.begin(), all.end(), eng);
        all.resize(m);
        if (shuffle_edges) rnd::shuffle(all.begin(), all.end(), eng);
        return all;
    }

    std::unordered_set<u64> st;
    st.reserve((std::size_t)m * 2 + 16);

    std::vector<edge> res;
    res.reserve(m);

    int tries = 0;
    const int max_tries = std::max(100000, m * 50 + 1000);
    while ((int)res.size() < m) {
        int i = rnd::uniform<int>(0, n - 1, eng);
        int j = rnd::uniform<int>(0, n - 1, eng);
        if (i == j) { if (++tries > max_tries) break; continue; }
        if (i > j) std::swap(i, j);
        int u = ord[i], v = ord[j]; // ensure acyclic
        u64 key = pack_directed(u, v);
        if (st.insert(key).second) {
            res.emplace_back(u, v);
        } else {
            if (++tries > max_tries) break;
        }
    }

    if ((int)res.size() < m) {
        if (maxE <= enum_threshold) {
            auto all = enumerate_all_dag_edges(ord);
            rnd::shuffle(all.begin(), all.end(), eng);
            for (auto [u, v] : all) {
                if ((int)res.size() == m) break;
                u64 key = pack_directed(u, v);
                if (st.insert(key).second) res.emplace_back(u, v);
            }
        } else {
            assert((int)res.size() == m && "dag: unable to sample enough unique edges");
        }
    }

    if (shuffle_edges) rnd::shuffle(res.begin(), res.end(), eng);
    return res;
}

inline std::vector<edge> dag(int n, int m, int base, bool shuffle_edges) {
    return dag(n, m, rnd::rng(), base, shuffle_edges);
}

template <class W, class Engine>
inline std::vector<std::tuple<int, int, W>> with_weights(
    const std::vector<edge>& edges, W wL, W wR, Engine& eng
) {
    std::vector<std::tuple<int, int, W>> res;
    res.reserve(edges.size());
    for (auto [u, v] : edges) {
        W w = rnd::uniform<W>(wL, wR, eng);
        res.emplace_back(u, v, w);
    }
    return res;
}

template <class W>
inline std::vector<std::tuple<int, int, W>> with_weights(
    const std::vector<edge>& edges, W wL, W wR
) {
    return with_weights<W>(edges, wL, wR, rnd::rng());
}

} // namespace graph

// ============================================================================
// str: strings
// ============================================================================
namespace str {

template <class Engine>
inline std::string random_string(int n, std::string_view alphabet, Engine& eng) {
    assert(n >= 0);
    assert(!alphabet.empty());
    std::string s;
    s.resize((std::size_t)n);
    const int m = (int)alphabet.size();
    for (int i = 0; i < n; i++) {
        int idx = rnd::uniform<int>(0, m - 1, eng);
        s[(std::size_t)i] = alphabet[(std::size_t)idx];
    }
    return s;
}

inline std::string random_string(int n, std::string_view alphabet) {
    return random_string(n, alphabet, rnd::rng());
}

template <class Engine>
inline std::string lowercase(int n, Engine& eng) {
    return random_string(n, "abcdefghijklmnopqrstuvwxyz", eng);
}
inline std::string lowercase(int n) { return lowercase(n, rnd::rng()); }

template <class Engine>
inline std::string uppercase(int n, Engine& eng) {
    return random_string(n, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", eng);
}
inline std::string uppercase(int n) { return uppercase(n, rnd::rng()); }

template <class Engine>
inline std::string binary(int n, Engine& eng, double p1) {
    assert(0.0 <= p1 && p1 <= 1.0);
    std::bernoulli_distribution dist(p1);
    std::string s;
    s.resize((std::size_t)n);
    for (int i = 0; i < n; i++) s[(std::size_t)i] = dist(eng) ? '1' : '0';
    return s;
}

inline std::string binary(int n, double p1) {
    return binary(n, rnd::rng(), p1);
}

} // namespace str

// ============================================================================
// io: printing helpers
// ============================================================================
namespace io {

template <class T>
inline void print_one(std::ostream& os, const T& x) {
    os << x;
}

template <class T>
inline void print_vec(std::ostream& os,
                      const std::vector<T>& a,
                      char sep = ' ',
                      char end = '\n') {
    for (std::size_t i = 0; i < a.size(); i++) {
        if (i) os << sep;
        os << a[i];
    }
    os << end;
}

template <class A, class B>
inline void print_pairs(std::ostream& os,
                        const std::vector<std::pair<A, B>>& ps,
                        char sep_in_pair = ' ',
                        char end_each = '\n') {
    for (auto const& [x, y] : ps) {
        os << x << sep_in_pair << y << end_each;
    }
}

inline void print_edges(std::ostream& os,
                        const std::vector<graph::edge>& edges,
                        char end_each = '\n') {
    for (auto const& [u, v] : edges) {
        os << u << ' ' << v << end_each;
    }
}

template <class W>
inline void print_wedges(std::ostream& os,
                         const std::vector<std::tuple<int, int, W>>& edges,
                         char end_each = '\n') {
    for (auto const& [u, v, w] : edges) {
        os << u << ' ' << v << ' ' << w << end_each;
    }
}

inline void print_graph(std::ostream& os,
                        int n,
                        const std::vector<graph::edge>& edges,
                        bool with_header = false,
                        char end_each = '\n') {
    if (with_header) os << n << ' ' << edges.size() << '\n';
    print_edges(os, edges, end_each);
}

template <class W>
inline void print_wgraph(std::ostream& os,
                         int n,
                         const std::vector<std::tuple<int, int, W>>& edges,
                         bool with_header = true,
                         char end_each = '\n') {
    if (with_header) os << n << ' ' << edges.size() << '\n';
    print_wedges(os, edges, end_each);
}

} // namespace io

} // namespace gen
