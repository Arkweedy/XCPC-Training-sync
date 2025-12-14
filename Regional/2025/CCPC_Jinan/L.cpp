#include<bits/stdc++.h>

using ll = long long;
using namespace std;

constexpr int N = 1e5 + 10;

template<typename T>
struct Fenwick{
    int n;
    vector<T>a;

    Fenwick(int n_)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        a.assign(n_, T{});
    }

    void add(int x, const T&v)
    {
        //cerr << "add " << x << " " << v << endl;
        for(int i = x + 1;i <= n;i += i&-i){
            a[i - 1] = a[i - 1] + v;
        }
    }

    T sum(int x)
    {
        T ans{};
        for(int i = x;i > 0;i -= i& -i){
            ans = ans + a[i - 1];
        }   
        return ans;
    }

    T query(int l, int r)
    {
        return sum(r) - sum(l);
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
    }
    
    Fenwick<ll>t(n * 2);
    vector<int>fa(n + n - 1);
    vector<int>val(n + n - 1);
    vector<pair<int,int>>son(n + n - 1);
    vector<int>out(n - 1);
    int p = 0;
    for(int i = n;i < n + n - 1;i++){
        son[i] = {p, p + 1};
        fa[p] = fa[p + 1] = i;
        p += 2;
    }

    for(int i = 0;i < n;i++){
        val[i] = a[i];
    }
    for(int i = n;i < n + n - 1;i++){
        auto [l, r] = son[i];
        val[i] = min(val[l], val[r]);
        out[i - n] = max(val[l],val[r]);
        t.add(i - n, out[i - n]);
    }

    

    auto upt = [&](int p)->void
    {
        do{
            p = fa[p];
            t.add(p - n, -out[p - n]);
            auto [l, r] = son[p];
            val[p] = min(val[l], val[r]);
            out[p - n] = max(val[l],val[r]);
            t.add(p - n, out[p - n]);
        }while(p != n + n - 2);
        return;
    };

    while(m--){
        char op;
        int l, r;
        cin >> op >> l >> r;
        l--, r--;
        if(op == 'A'){
            ll ans = t.query(l, r + 1);
            // ll ans = 0;
            // for(int i = l;i <= r;i++){
            //     ans += out[i];
            // }
            cout << ans << "\n";
        }
        else{
            swap(val[l], val[r]);
            upt(l);
            upt(r);
            // for(int i = 0;i < n + n - 1;i ++){
            //     cerr << val[i] <<" ";
            // }
            // cerr << endl;
            // for(int i = 0;i < n - 1;i++){
            //     cerr << out[i]<<" ";
            // }
            // cerr << endl;
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
