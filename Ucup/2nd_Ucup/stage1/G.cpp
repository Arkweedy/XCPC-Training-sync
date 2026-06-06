#include<bits/stdc++.h>
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

using namespace std;

//G.cpp Create time : 2026.05.27 17:14

struct segtree{
    int n;
    int vc;
    vector<int>a;
    vector<int>rt,ls,rs;
    vector<int>t;

    segtree(int n_): n(n_), vc(0)
    {
        rt.reserve(n * 5);
        ls.reserve(n * 30);
        rs.reserve(n * 30);
        t.reserve(n * 30);
    }

    segtree(int n_, vector<int>_a): n(n_), vc(0), a(_a)
    {
        rt.reserve(n * 5);
        ls.reserve(n * 30);
        rs.reserve(n * 30);
        t.reserve(n * 30);
        int p = newNode();
        newVersion(p);
        build(0, n - 1, rt[0]);
    }

    int newNode()
    {
        ls.emplace_back();
        rs.emplace_back();
        t.emplace_back();
        return t.size() - 1;
    }

    void newVersion(int root)
    {
        rt.push_back(root);
        vc++;
    }

    void build(int l, int r, int p)
    {
        if(l == r){
            t[p] = a[l];
            return;
        }
        int m = l + r >> 1;
        ls[p] = newNode();
        rs[p] = newNode();
        build(l, m, ls[p]);
        build(m + 1, r, rs[p]);
        push(p);
        return;
    }

    void push(int p)
    {
        t[p] = t[ls[p]] + t[rs[p]];
    }

    int apply(int x, int val, int l, int r, int p)
    {
        if(l == r){
            int np = newNode();
            t[np] = t[p] + val;
            return np;
        }
        int m = l + r >> 1;
        int np = newNode();
        if(x <= m){
            int s = apply(x, val, l ,m, ls[p]);
            ls[np] = s;
            rs[np] = rs[p];
        }
        else{
            int s = apply(x, val, m + 1, r, rs[p]);
            ls[np] = ls[p];
            rs[np] = s;
        }
        push(np);
        return np;
    }

    int rangeLeq(int lp, int rp, int L)
    {
        //cerr << "#" << L << endl;
        return query(L, 0, n - 1, rt[rp + 1]) - query(L, 0, n - 1, rt[lp]);
    }

    int query(int x, int l, int r, int p)
    {
        if(x < 0)return 0;
        if(l == r){
            return t[p];
        }
        int m = l + r >> 1;
        if(x <= m){
            return query(x, l, m, ls[p]);
        }
        else{
            return t[ls[p]] + query(x, m + 1, r, rs[p]);
        }
    }

    void apply(int ver, int x, int val)
    {
        newVersion(apply(x, val, 0, n - 1, rt[ver]));
        return;
    }
};

void solve()
{
    int n;
    cin >> n;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
        a[i]--;
    }

    segtree t(n, vector<int>(n, 0));
    for(int i = 0;i < n;i++){
        t.apply(i, a[i], 1);
    }

    auto calc = [&](int l, int r)->i64
    {
        i64 res = 0;
        for(int i = l;i <= r;i++){
            res += t.rangeLeq(i, r, a[i] - 1);
        }
        return res;
    };


    // 1. 找当前所在的区间
    // 2. 知道当前所在区间的答案

    multiset<i64>s;
    i64 z = calc(0, n - 1);
    s.insert(z);
    vector<int>use(n);
    set<pair<int,i64>>st; // {l, cnt} // 
    st.insert({0, z});
    st.insert({n, 0});

    constexpr i64 inf = 1e18;
    
    for(int i = 0;i < n;i++){
        cout << z << " ";
        i64 p;
        cin >> p;
        p ^= z;
        p--;
        assert(p < n && p >= 0);
        //[L,R,ans]
        int lok = 1, rok = 1;
        if(p == 0 || use[p - 1] == 1)lok = 0;
        if(p == n - 1 || use[p + 1] == 1)rok = 0;
        use[p] = 1;
        if(lok && rok){
            auto [l, val] = *(prev(st.lower_bound({p, inf})));
            auto [r, _] = *(st.lower_bound({p, inf}));
            r--;
            int m = p;
            //[l, m - 1] [m + 1, r]
            if(m - l < r - m){ // L
                i64 Lval = calc(l, m - 1);
                i64 LMtoMR = 0;
                for(int i = l;i <= m;i++){
                    LMtoMR += t.rangeLeq(m, r, a[i] - 1);
                }
                i64 Rval = val - Lval - LMtoMR;
                s.extract(val);
                s.insert(Lval);
                s.insert(Rval);
                st.erase({l ,val});
                st.insert({l, Lval});
                st.insert({m, 0});
                st.insert({m + 1, Rval});
            }
            else{
                i64 Rval = calc(m + 1, r);
                i64 MRtoLM = 0;
                for(int i = m;i <= r;i++){//[l,m]
                    MRtoLM += m - l + 1 - t.rangeLeq(l, m, a[i]);
                }
                i64 Lval = val - Rval - MRtoLM;
                s.extract(val);
                s.insert(Lval);
                s.insert(Rval);
                st.erase({l ,val});
                st.insert({l, Lval});
                st.insert({m, 0});
                st.insert({m + 1, Rval});
            }
        }
        else if(lok){ // [l, r] -> {l, cnt}
            auto [l, val] = *(prev(st.lower_bound({p, inf})));
            int r = p;
            i64 nval = val - (r - l - t.rangeLeq(l, r - 1, a[r]));
            s.extract(val);
            s.insert(nval);
            st.erase({l, val});
            st.insert({l, nval});
            st.insert({r, 0});
        }
        else if(rok){
            auto [l, val] = *(prev(st.lower_bound({p, inf})));
            auto [r, _] = *(st.lower_bound({p, inf}));
            r--;
            i64 nval = val - t.rangeLeq(l + 1, r, a[l] - 1); 
            s.extract(val);
            s.insert(nval);
            st.erase({l, val});
            st.insert({l, 0});
            st.insert({l + 1, nval});
        }
        else{
            s.extract(0);
        }
        if(s.empty())z = 0;
        else z = *prev(s.end());
        
    }
    cout << endl;
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