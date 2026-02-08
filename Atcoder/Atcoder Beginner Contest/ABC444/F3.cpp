#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//F.cpp Create time : 2026.02.07 20:47

bool check_k(const vector<i64>& A, i64 M, i64 k) {
    const i64 n = (i64)A.size();
    const i64 h = (n + M) / 2;
    if (k <= 1) return true;

    i64 op = 0;          // 已经做掉的“+1”操作次数（拆 l>=2k）
    i64 G  = 0;          // 做完所有“+1”后，>=k 的棍子数
    i64 ge_init = 0;     // 初始 >=k 的棍子数（用于 op>=M 分支）
    i128 waste_small = 0;// 来自 <k 区间棍子的可“无损消耗”操作数
    i64 cnt_eq = 0;      // 长度==2k-1 的棍子数
    unordered_map<i64,i64> cnt; // 只存 [k,2k-2] 的长度计数
    cnt.reserve(A.size()*2 + 10);

    auto add_piece = [&](i64 len, i64 c){
        if (c == 0) return;
        if (len == 2*k - 1) cnt_eq += c;
        else cnt[len] += c; // 这里 len 一定在 [k,2k-2]（做完“+1”后不会 >=2k）
    };

    for (i64 a : A) {
        if (a < k) {
            waste_small += (i128)(a - 1);
            continue;
        }
        ge_init++;

        // p = 2^{floor(log2(a/k))}
        i64 q = a / k;                 // q>=1
        int t = 63 - __builtin_clzll((unsigned long long)q);
        i64 p = 1LL << t;

        // 完全做掉这根的“+1”拆分：操作 (p-1)，得到 p 根 >=k
        op += (p - 1);
        G  += p;

        // 这 p 根只会是 base / base+1 两种
        i64 base = a / p;
        i64 rem  = a % p;
        add_piece(base,     p - rem);
        add_piece(base + 1, rem);
    }

    // 分支1：只用“+1”操作就能做满 M 次
    if (op >= M) {
        // 只要有足够多的“+1”节点可拆，就能做到 G = ge_init + M
        return (ge_init + M) > h;
    }

    // 还要做 R 次操作
    i64 R = M - op;

    // 2k-1 每根可无损吞 (k-1) 次操作：1次拆成(k,k-1) + (k-2)次继续拆 k-1
    i128 free_ops = waste_small + (i128)cnt_eq * (k - 1);
    if (free_ops >= R) {
        return G > h;
    }

    // deficit：必须牺牲 >=k 的棍子
    i128 need = (i128)R - free_ops;

    // 当 need>0 时，意味着 2k-1 的 free 也已经用满了；此时每个 2k-1 都变成了一根 k（>=k）
    cnt[k] += cnt_eq;

    vector<pair<i64,i64>> items;
    items.reserve(cnt.size());
    for (auto &e : cnt) {
        if (e.first >= k && e.first <= 2*k - 2) items.push_back(e);
    }
    sort(items.begin(), items.end(), [&](auto &x, auto &y){ return x.first > y.first; });

    i64 destroyed = 0;
    for (auto [len, c] : items) {
        if (need <= 0) break;
        i128 cap = (i128)(len - 1) * c;   // 牺牲这批最多能补多少操作
        if (cap >= need) {
            i128 per = (len - 1);
            i128 take = (need + per - 1) / per; // 需要牺牲多少根
            destroyed += (i64)take;
            need = 0;
            break;
        } else {
            destroyed += c;
            need -= cap;
        }
    }

    i64 G_final = G - destroyed;
    return G_final > h;
}

void solve()
{
    i64 n;
    cin >> n;
    i64 m;
    cin >> m;
    vector<i64>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    sort(a.begin(),a.end());
    i64 h = (n + m) / 2;

    

    int l = 1, r = a.back() + 1;
    while(r - l > 1){
        int M = l + r >> 1;
        if(check_k(a, m, M)){
            l = M;
        }
        else{
            r = M;
        }
    }


    cout << l << endl;
    return;

}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}