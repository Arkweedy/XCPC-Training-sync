#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

template <typename T>
struct Fenwick {
    int n;
    vector<T> a;
    
    Fenwick(int n_ = 0) {
        init(n_);
    }
    
    void init(int n_) {
        n = n_;
        a.assign(n, T{});
    }
    
    void add(int x, const T &v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] = a[i - 1] + v;
        }
    }
    
    T sum(int x) {
        T ans{};
        for (int i = x; i > 0; i -= i & -i) {
            ans = ans + a[i - 1];
        }
        return ans;
    }
    
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }
    
    int select(const T &k) {
        int x = 0;
        T cur{};
        for (int i = 1 << __lg(n); i; i /= 2) {
            if (x + i <= n && cur + a[x + i - 1] <= k) {
                x += i;
                cur = cur + a[x - 1];
            }
        }
        return x;
    }
};

void solve()
{
    int n;
    cin>>n;
    vector<int>a(n);
    map<int,vector<int>>mpa;
    for(int i = 0;i < n;i++){
        cin>>a[i];
        a[i] += i;
        mpa[a[i]].push_back(i);
    }
    vector<int>b(n);
    map<int,vector<int>>mpb;
    for(int i = 0;i < n;i++){
        cin>>b[i];
        b[i] += i;
        mpb[b[i]].push_back(i);
    }

    vector<int>endpos(n);
    
    for(auto [x, va] : mpa){
        auto vb = mpb[x];
        if(va.size() != vb.size()){
            cout<<-1<<endl;
            return;
        }
        else{
            for(int i = 0;i < va.size();i++){
                endpos[va[i]] = vb[i]; 
            }
        }
    }
    Fenwick<int>t(n + 1);
    ll ans = 0;
    for(int i = 0;i < n;i++){
        ans += t.rangeSum(0, endpos[i]);
        t.add(endpos[i], 1);
    }
    ans = 1ll * n * (n - 1) / 2 - ans;
    cout<<ans<<endl;
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int tt = 1;
    //cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}