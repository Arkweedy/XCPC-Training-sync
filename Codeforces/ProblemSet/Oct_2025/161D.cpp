#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using poly = vector<ll>;

static vector<int> REV_FFT;
static vector<complex<long double>> ROOTS_FFT{ {0,0}, {1,0} }; // 与 NTT 模板同构的根表扩展

static inline void ensure_rev_roots(int n){
    if ((int)REV_FFT.size() != n){
        REV_FFT.assign(n, 0);
        int k = __builtin_ctz(n) - 1;
        for (int i = 0; i < n; ++i){
            REV_FFT[i] = (REV_FFT[i>>1] >> 1) | ((i & 1) << k);
        }
    }
    if ((int)ROOTS_FFT.size() < n){
        int k = __builtin_ctz((int)ROOTS_FFT.size());
        ROOTS_FFT.resize(n);
        while ((1 << k) < n){
            // 每次把区间 [2^{k-1}, 2^k) 扩为 [2^k, 2^{k+1})
            long double ang = acosl(-1.0L) / (1 << k); // π / 2^k
            complex<long double> e(cosl(ang), sinl(ang));
            for (int i = (1 << (k - 1)); i < (1 << k); ++i){
                ROOTS_FFT[2 * i]     = ROOTS_FFT[i];
                ROOTS_FFT[2 * i + 1] = ROOTS_FFT[i] * e;
            }
            ++k;
        }
    }
}

static inline void dft_fft(vector<complex<long double>>& a){
    int n = (int)a.size();
    ensure_rev_roots(n);
    for (int i = 0; i < n; ++i) if (REV_FFT[i] < i) swap(a[i], a[REV_FFT[i]]);
    for (int len = 1; len < n; len <<= 1){
        for (int i = 0; i < n; i += (len << 1)){
            // 使用 roots[len + j]
            for (int j = 0; j < len; ++j){
                auto u = a[i + j];
                auto v = a[i + j + len] * ROOTS_FFT[len + j];
                a[i + j]       = u + v;
                a[i + j + len] = u - v;
            }
        }
    }
}
static inline void idft_fft(vector<complex<long double>>& a){
    if (a.size() <= 1) return;
    reverse(a.begin() + 1, a.end()); // 与 dft_fft 的根表匹配（同 NTT 写法）
    dft_fft(a);
    long double inv_n = 1.0L / (long double)a.size();
    for (auto &x : a) x *= inv_n;
}

static constexpr int NAIVE_TH = 64; // 小规模阈值（可按评测调）

static inline poly conv_fft(const poly& A, const poly& B){
    if (A.empty() || B.empty()) return {};
    int nA = (int)A.size(), nB = (int)B.size();
    int tot = nA + nB - 1;
    if (min(nA, nB) <= NAIVE_TH){
        poly C(tot, 0);
        for (int i = 0; i < nA; ++i){
            if (!A[i]) continue;
            long double ai = (long double)A[i];
            for (int j = 0; j < nB; ++j){
                C[i + j] += (ll)(ai * (long double)B[j]);
            }
        }
        return C;
    }
    int n = 1; while (n < tot) n <<= 1;
    vector<complex<long double>> FA(n), FB(n);
    for (int i = 0; i < nA; ++i) FA[i] = complex<long double>((long double)A[i], 0.0L);
    for (int i = nA; i < n; ++i) FA[i] = {0.0L, 0.0L};
    for (int i = 0; i < nB; ++i) FB[i] = complex<long double>((long double)B[i], 0.0L);
    for (int i = nB; i < n; ++i) FB[i] = {0.0L, 0.0L};

    dft_fft(FA);
    dft_fft(FB);
    for (int i = 0; i < n; ++i) FA[i] *= FB[i];
    idft_fft(FA);

    poly C(tot);
    for (int i = 0; i < tot; ++i){
        // 四舍五入恢复整数；加入微小容差防止 -0 / 1e-12 抖动
        long double x = FA[i].real();
        C[i] = (ll) llroundl(x);
    }
    return C;
}

// ======================= 工具函数（无模） =======================
static inline void trim(poly &f){
    while (!f.empty() && f.back() == 0) f.pop_back();
}

static inline void add_shift(poly &dst, const poly &src, int sh){
    if (src.empty()) return;
    if ((int)dst.size() < (int)src.size() + sh) dst.resize((int)src.size() + sh, 0LL);
    for (int i = 0; i < (int)src.size(); ++i) dst[i + sh] += src[i];
}

// ======================= 树上各距离路径计数（精确） =======================
// 结构：与上一版 vector<int>/NTT 板子一致（长链剖分 + 节点内分治 + 链内CDQ）
// 但计数用 long long，卷积用 conv_fft。

struct TreePathsAllDistancesExact {
    int n;
    vector<vector<int>> g;

    vector<int> fa, dep, siz, heavy, top;
    vector<poly> sub, Plight;  // sub[v]：整棵子树深度分布；Plight[v]：v 的“轻部分+自身”
    vector<ll> dist;           // dist[k]：长度为 k 的无序路径条数（精确计数）

    TreePathsAllDistancesExact(int n)
        : n(n), g(n), fa(n,-1), dep(n,0), siz(n,0),
          heavy(n,-1), top(n,-1), sub(n), Plight(n), dist(n, 0LL) {}

    inline void add_edge(int u, int v){ g[u].push_back(v); g[v].push_back(u); }

    // 1) size 与重儿子
    void dfs_sz(int u, int p){
        fa[u] = p; siz[u] = 1; int mx = 0;
        for (int v : g[u]) if (v != p){
            dep[v] = dep[u] + 1;
            dfs_sz(v, u);
            siz[u] += siz[v];
            if (siz[v] > mx) mx = siz[v], heavy[u] = v;
        }
    }

    inline void add_to_dist(const poly &a){
        int up = min<int>(n, (int)a.size());
        for (int i = 1; i < up; ++i) dist[i] += a[i]; // i=0 同点忽略
    }

    // 轻儿子两两配对（索引分治方式，避免 child 数组的多份拷贝）
    poly merge_add_pairs_idx(const vector<int> &ids, int l, int r){
        if (l >= r) return {};
        if (l + 1 == r){
            poly base = sub[ids[l]];
            base.insert(base.begin(), 0LL); // << 1
            return base;
        }
        int m = (l + r) >> 1;
        poly L = merge_add_pairs_idx(ids, l, m);
        poly R = merge_add_pairs_idx(ids, m, r);
        if (!L.empty() && !R.empty()){
            poly C = conv_fft(L, R);
            add_to_dist(C);
        }
        if (L.size() < R.size()) L.resize(R.size(), 0LL);
        for (int i = 0; i < (int)R.size(); ++i) L[i] += R[i];
        trim(L);
        return L;
    }

    // 2) DP（重儿子优先 + 偷容器 + 用后清空）
    void dfs_poly(int u, int p){
        int hv = heavy[u];
        if (hv != -1) dfs_poly(hv, u);
        for (int v : g[u]) if (v != p && v != hv) dfs_poly(v, u);

        // sub[u] = (sub[hv]<<1) + 1 + Σ_{light}(sub[v]<<1)
        if (hv != -1) sub[u] = std::move(sub[hv]);
        else sub[u].clear();
        sub[u].insert(sub[u].begin(), 0LL);      // <<1
        if (sub[u].empty()) sub[u].push_back(1LL);
        else sub[u][0] += 1LL;

        vector<int> lightIds;
        lightIds.reserve(max(0, (int)g[u].size()-1));
        for (int v : g[u]) if (v != p && v != hv){
            add_shift(sub[u], sub[v], 1);
            lightIds.push_back(v);
        }
        trim(sub[u]);

        // Plight[u] = 1 + Σ_{light}(sub[v]<<1)
        Plight[u].assign(1, 1LL);
        for (int v : lightIds) add_shift(Plight[u], sub[v], 1);
        trim(Plight[u]);

        // 节点内部：自点与轻部分
        add_to_dist(Plight[u]);

        // 轻儿子之间：分治合并（跨半区卷积一次）
        if (!lightIds.empty()){
            (void)merge_add_pairs_idx(lightIds, 0, (int)lightIds.size());
        }

        // 轻儿子 sub 用后清空，控制峰值内存
        for (int v : lightIds){
            poly empty; empty.swap(sub[v]);
        }
    }

    // 3) HLD
    void dfs_hld(int u, int tp){
        top[u] = tp;
        if (heavy[u] != -1) dfs_hld(heavy[u], tp);
        for (int v : g[u]) if (v != fa[u] && v != heavy[u]) dfs_hld(v, v);
    }

    // 4) 链内 CDQ：跨半区一次卷积
    void cdq_chain(const vector<int>& nds, int L, int R){
        if (R - L <= 1) return;
        int M = (L + R) >> 1;

        cdq_chain(nds, L, M);
        cdq_chain(nds, M, R);

        poly A, B;
        for (int i = L; i < M; ++i) add_shift(A, Plight[nds[i]], (M - 1 - i));
        for (int j = M; j < R; ++j) add_shift(B, Plight[nds[j]], (j - M + 1));
        trim(A); trim(B);

        if (!A.empty() && !B.empty()){
            poly C = conv_fft(A, B);
            add_to_dist(C);
        }
    }

    void work(int root = 0){
        dfs_sz(root, -1);
        dfs_poly(root, -1);
        dfs_hld(root, root);

        for (int u = 0; u < n; ++u) if (top[u] == u){
            vector<int> nds;
            int x = u;
            while (x != -1){
                nds.push_back(x);
                x = heavy[x];
            }
            cdq_chain(nds, 0, (int)nds.size());
        }
    }

    // 返回 dist[1..n-1]
    vector<ll> get_dist() const { return dist; }
};


void solve()
{
    int n, k;
    cin>>n>>k;
    TreePathsAllDistancesExact solver(n);
    for (int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        u--;
        v--;
        solver.add_edge(u,v);
    }
    solver.work(0); // 以 0 为根（不影响结果）

    auto d = solver.get_dist();
    if(k > n){
        cout<<0<<endl;
        return;
    }
    cout<<d[k]<<endl;
    return;
    
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
