#include<bits/stdc++.h>
using i64 = long long;
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;

using namespace std;

constexpr int N = 1e7 + 10;
vector<int>prime;
bitset<N + 1>isprime;
vector<int>mu;

void seive()
{
    isprime.set();
    mu.resize(N + 1);
    isprime[0] = isprime[1] = 0;
    mu[1] = 1;
    for (int i = 2; i <= N; i++) {
        if (isprime[i]) {
            prime.push_back(i);
            mu[i] = -1;
        }
        for (auto &p : prime) {//p = lpf[i * p]
            if (p * i > N)
                break;
            isprime.flip(i * p);
            //mu
            if (i % p == 0) {
                mu[i * p] = 0;
                break;
            }
            else {
                mu[i * p] = mu[i] * (-1);
            }
        }
    }
}

class DSU
{
    int n;
    vector<int>fa;
    vector<int>sz;
    

public:
    int scc;

    DSU(int n)
    {
        this->n = n;
        scc = n;
        fa.resize(n);
        sz.resize(n);
        for (int i = 0; i < n; i++) {
            fa[i] = i;
            sz[i] = 1;
        }
    }

    int find(int p)
    {
        return fa[p] == p ? p : (fa[p] = find(fa[p]));
    }

    bool same(int u, int v)
    {
        return find(u) == find(v);
    }

    int size(int p)
    {
        return sz[find(p)];
    }

    bool merge(int u, int v)
    {
        int fu = find(u), fv = find(v);
        if (fu == fv) {
            return false;
        }
        else {
            if (sz[fu] < sz[fv]) {
                swap(fu, fv);
            }
            scc--;
            sz[fu] += sz[fv];
            fa[fv] = fu;
            return true;
        }
    }
};

void solve()
{
    int n, x;
    cin>>n>>x;
    vector<pair<int,int>>e;
    for(int i = 0;i < n - 1;i++){
        int u,v;
        cin>>u>>v;
        u--,v--;
        e.emplace_back(u,v);
    }
    vector<int>a(n);
    for(int i = 0;i < n;i++){
        cin>>a[i];
    }

    vector<int>fac;
    for(int i = 1;i * i <= x;i++){
        if(x % i == 0){
            fac.push_back(i);
            if(i * i != x){
                fac.push_back(x / i);
            }
        }
    }

    ll ans = 0;
    for(auto d : fac){
        DSU dsu(n);
        for(const auto &[u,v] : e){
            if(d % a[u] == 0 && d % a[v] == 0){
                dsu.merge(u,v);
            }
        }
        ll sum = 0;
        for(int i = 0;i < n;i++){
            if(dsu.find(i) == i && d % a[i] == 0){
                ll sz = dsu.size(i);
                sum += sz * (sz + 1) / 2;
            }
        }
        ans += sum * mu[x / d];
    }
    cout<<ans<<endl;
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    seive();
    int tt = 1;
    cin >> tt;
    while(tt--){
        solve();
    }
    return 0;
}